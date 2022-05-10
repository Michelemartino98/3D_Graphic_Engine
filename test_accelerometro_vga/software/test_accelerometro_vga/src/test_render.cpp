
#include "../inc/config.h"

#define ABS(x)	((x >= 0) ? (x) : (-(x)))

alt_up_pixel_buffer_dma_dev *pixel_buf_dma_dev;
alt_up_accelerometer_spi_dev * accelerometer_dev;

uint8_t display_digit(uint8_t val){
	uint8_t lut[20] = {0x3F, 0x06, 0x5B, 0x4F, 	//0 to 3
					   0x66, 0x6D, 0x7D, 0x07,	//4 to 7
					   0x7F, 0x6F, 0x77, 0x7C,  //8 to B
					   0x39, 0x5E, 0x79, 0x71,  //C to F
					   0x00, 0x40, 0x5E, 0x76};	//0x00 codifica il display spento -> NO_NUMBER, 0x40 codifica il meno;
	return (lut[val]);
}
void display_fps(uint32_t fps){
    uint8_t units, tens, hundreds;
	
	hundreds = (fps / 100) ? (fps / 100) : NO_NUMBER ;
	tens = (fps % 100) / 10;
	tens = ((hundreds == NO_NUMBER) && (tens == 0)) ? NO_NUMBER : tens;
	units = fps % 10;
	HEX3_HEX0_DATA_REG = display_digit(units) << FIRST_DISPLAY | display_digit(tens) << SECOND_DISPLAY | display_digit(hundreds) << THIRD_DISPLAY ;

}

int main(){


    Cube_3D Cube;
    int current_frame = 0;

    pixel_buf_dma_dev = alt_up_pixel_buffer_dma_open_dev("/dev/video_pixel_buffer_dma_0");
    accelerometer_dev = alt_up_accelerometer_spi_open_dev ("/dev/accelerometer_spi_0");
    alt_timestamp_start();
//#ifdef DEBUG_1
    if ( accelerometer_dev == NULL)
        printf ("Error: could not open acc device \n");
    else
        printf ("Opened acc device \n");
//#endif
    //parametri per uso dell'accelerometro+slider
    int32_t x_acc = 0;
    int32_t y_acc = 0;
    int32_t z_acc = 0; 

    uint16_t slider_data_reg;
    uint16_t edge_capture_k1;
    bool command_sw=true; 

    float inc_tx=0;
    float inc_ty=0;

    float inc_rx=0;
    float inc_ry=0;

    uint32_t fps;

    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(KEY_BASE, BIT(KEY1));

    //spengo i display 7 seg
    HEX3_HEX0_DATA_REG = 0xFFFF;
    HEX5_HEX4_DATA_REG = 0xFFFF;
    //IOWR_ALTERA_AVALON_PIO_DATA(HEX3_HEX0_BASE, 0);
    for(;;){
        slider_data_reg = IORD_ALTERA_AVALON_PIO_DATA(SLIDERS_BASE);
        alt_up_accelerometer_spi_read_x_axis(accelerometer_dev, &x_acc);
        alt_up_accelerometer_spi_read_y_axis(accelerometer_dev, &y_acc);
        alt_up_accelerometer_spi_read_z_axis(accelerometer_dev, &z_acc);

        //uso key1 per passare dal controllo della rotazione a quello della traslazione tramite accelerometro
        edge_capture_k1 =  IORD_ALTERA_AVALON_PIO_EDGE_CAP(KEY_BASE) & BIT(KEY1);
        if( edge_capture_k1 ) {
            command_sw=!command_sw;
            edge_capture_k1 = 0;
            IOWR_ALTERA_AVALON_PIO_EDGE_CAP(KEY_BASE, BIT(KEY1));
        }
        //ROTAZIONE
        if(command_sw){
            if( ABS(x_acc) > ACC_TH && ABS(y_acc) > ACC_TH){
                inc_rx= (float)y_acc / G_ACC * MAX_INC_R;
                Cube.update_rotation_relative( inc_rx, X);
                inc_ry= (float)x_acc / G_ACC * MAX_INC_R;
                Cube.update_rotation_relative( inc_ry, Z);
            }
        }
        //TRASLAZIONE
        else{
            if( ABS(x_acc) > ACC_TH && ABS(y_acc) > ACC_TH){
                inc_tx= (float)-x_acc / G_ACC * MAX_INC_T;
                Cube.update_translation_relative(inc_tx , X);
                inc_ty= (float)y_acc / G_ACC * MAX_INC_T;
                Cube.update_translation_relative(inc_ty , Y);
            } 
        }
        //SCALA
        if(slider_data_reg & BIT(9)){                       //il segno dell'incremento della scala sta su slider9    
            if(slider_data_reg & BIT(0)){                   //scala x
                Cube.update_scaling_relative( INC_S , X );
            }
            if(slider_data_reg & BIT(1)){                   //scala y
                Cube.update_scaling_relative( INC_S , Y );
            }
            if(slider_data_reg & BIT(2)){                   //scala z
                Cube.update_scaling_relative( INC_S , Z );
            }
        }
        else {                                              //incremento negativo
            if(slider_data_reg & BIT(0)){ 
                Cube.update_scaling_relative( -INC_S , X );
            }
            if(slider_data_reg & BIT(1)){ 
                Cube.update_scaling_relative( -INC_S , Y );
            }
            if(slider_data_reg & BIT(2)){ 
                Cube.update_scaling_relative( -INC_S , Z );
            }
        }
        #ifdef DEBUG_ACC
        printf("%f %f \n", inc_rx, inc_rz );
        #endif


        #ifdef DEBUG_1
    	printf("FRAME %d\n", current_frame++);
        #endif /*DEBUG_1*/

        Cube.calculate_rendering();
        Cube.display_frame(); 
        fps = TIMER_FREQ/alt_timestamp();
        //display_fps(fps);
        alt_timestamp_start();

    }
}

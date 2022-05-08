
#include "../inc/config.h"

alt_up_pixel_buffer_dma_dev *pixel_buf_dma_dev;
alt_up_accelerometer_spi_dev * accelerometer_dev;

int main(){


    Cube_3D Cube;
    int current_frame = 0;

    pixel_buf_dma_dev = alt_up_pixel_buffer_dma_open_dev("/dev/video_pixel_buffer_dma_0");
    accelerometer_dev = alt_up_accelerometer_spi_open_dev ("/dev/accelerometer_spi_0");

    if ( accelerometer_dev == NULL)
        printf ("Error: could not open acc device \n");
    else
        printf ("Opened acc device \n");
            
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

    for(;;){
        slider_data_reg = IORD_ALTERA_AVALON_PIO_DATA(SLIDERS_BASE);
        alt_up_accelerometer_spi_read_x_axis(accelerometer_dev, &x_acc);
        alt_up_accelerometer_spi_read_y_axis(accelerometer_dev, &y_acc);
        alt_up_accelerometer_spi_read_z_axis(accelerometer_dev, &z_acc);

        #ifdef C1
        //uso key1 per passare dal controllo della rotazione a quello della traslazione tramite accelerometro
        edge_capture_k1 = IORD_ALTERA_AVALON_PIO_EDGE_CAP(KEY_BASE);
        if( edge_capture_k1 & BIT(1) ) command_sw=!command_sw;
        IOWR_ALTERA_AVALON_PIO_EDGE_CAP(KEY_BASE, BIT(1));
        #else
        //trasla e ruota contemporaneamente
        command_sw=!command_sw; 
        #endif
        //ROTAZIONE
        if(command_sw){
            inc_rx= (float)y_acc / G_ACC * MAX_INC_R;
            Cube.update_rotation_relative( -inc_rx, X);
            inc_ry= (float)x_acc / G_ACC * MAX_INC_R;
            Cube.update_rotation_relative( inc_ry, Z);
        }
        //TRASLAZIONE
        else{
            inc_tx= (float)x_acc / G_ACC * MAX_INC_T;
            Cube.update_translation_relative(inc_tx , X);
            inc_ty= (float)y_acc / G_ACC * MAX_INC_T;
            Cube.update_translation_relative(inc_ty , Y);
        }
        //SCALA
        if(slider_data_reg & BIT(9)){   //il segno dell'incremento della scala sta su slider9    
            if(slider_data_reg & BIT(0)){ //scala x
                Cube.update_scaling_relative( INC_S , X );
            }
            if(slider_data_reg & BIT(1)){ //scala y
                Cube.update_scaling_relative( INC_S , Y );
            }
            if(slider_data_reg & BIT(2)){ //scala y
                Cube.update_scaling_relative( INC_S , Z );
            }
        }
        else {                            //incremento negativo
            if(slider_data_reg & BIT(0)){ //scala x
                Cube.update_scaling_relative( -INC_S , X );
            }
            if(slider_data_reg & BIT(1)){ //scala y
                Cube.update_scaling_relative( -INC_S , Y );
            }
            if(slider_data_reg & BIT(2)){ //scala y
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

    }
}

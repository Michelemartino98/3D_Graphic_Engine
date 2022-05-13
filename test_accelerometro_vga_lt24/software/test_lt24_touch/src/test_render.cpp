
#include "../inc/config.h"
//#include "../inc/ILI9341.h"
//#include "../inc/touch_spi.h"
//#include "../inc/alt_video_display.h"

alt_up_pixel_buffer_dma_dev *pixel_buf_dma_dev;

Cube_3D Cube;

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

    uint32_t fps;
    
    #ifdef DEBUG_1
    int current_frame = 0;
    #endif /*DEBUG_1*/

    init_accelerometer();
    pixel_buf_dma_dev = alt_up_pixel_buffer_dma_open_dev("/dev/video_pixel_buffer_dma_0");
    alt_timestamp_start();
    alt_video_display Display;

//    TOUCH_HANDLE *pTouch;
//        int delay , count ;
//        while (count<10) {
//        delay=0;
//        while (delay <200000) {delay++;}
//        count++;
//        }

//    // init touch
//    pTouch = Touch_Init(SPI_BASE, TOUCH_PEN_IRQ_N_BASE, TOUCH_PEN_IRQ_N_IRQ);
//    if (!pTouch){
//        printf("Failed to init touch\r\n");
//    }else{
//        printf("Init touch successfully\r\n");
//
//    }

    LCD_Init();
    //usleep(10000);
    LCD_Clear(WHITE);
    //usleep(10000);
    //vid_draw_circle(100,100,10,RED,1,Display);

    //demo lt24 per capire funzioni
    LCD_Pattern_Horizon();
    usleep(1000000);
    LCD_Pattern_Vertical();
    usleep(1000000);
    for(;;){
    	

        #ifdef DEBUG_1
    	printf("FRAME %d\n", current_frame++);
        #endif /*DEBUG_1*/



        accelerometer_controller();
        Cube.calculate_rendering();
        Cube.display_frame(); 
        fps = TIMER_FREQ/alt_timestamp();
        display_fps(fps);
        alt_timestamp_start();

    }
}

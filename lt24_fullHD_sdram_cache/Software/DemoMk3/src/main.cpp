
#include "../inc/config.h"

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
	//HEX3_HEX0_DATA_REG = display_digit(units) << FIRST_DISPLAY | display_digit(tens) << SECOND_DISPLAY | display_digit(hundreds) << THIRD_DISPLAY ;
    IOWR_ALTERA_AVALON_PIO_DATA(HEX3_HEX0_BASE, display_digit(units) << FIRST_DISPLAY | display_digit(tens) << SECOND_DISPLAY | display_digit(hundreds) << THIRD_DISPLAY);
}

int main(){

    uint32_t fps;
    
    #ifdef DEBUG_1
    int current_frame = 0;
    #endif /*DEBUG_1*/

    init_accelerometer();
    pixel_buf_dma_dev = alt_up_pixel_buffer_dma_open_dev("/dev/video_pixel_buffer_dma_0");
    alt_timestamp_start();

    
    
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

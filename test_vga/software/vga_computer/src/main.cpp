/*
 * main.cpp
 *
 *  Created on: 11 apr 2022
 *      Author: 39327
 */

#include "../inc/config.h"
#include "system.h"
#include "../../vga_computer_bsp/drivers/inc/altera_up_avalon_video_pixel_buffer_dma.h"


// define a pointer of type pixel_buffer...
// to use as a reference in the dma functions
//
alt_up_pixel_buffer_dma_dev *pixel_buf_dma_dev;


// open the Pixel Buffer port
// - command is in drivers/inc/alter...video_pixel_buffer_dma.h
// name reference is in system.h
// - "/dev/video_pixel_buffer_dma_0"
//

int main(){
	pixel_buf_dma_dev = alt_up_pixel_buffer_dma_open_dev("/dev/video_pixel_buffer_dma_0");
	alt_up_pixel_buffer_dma_clear_screen(pixel_buf_dma_dev,0);
	alt_up_pixel_buffer_dma_clear_screen(pixel_buf_dma_dev,1);
	alt_up_pixel_buffer_dma_draw(pixel_buf_dma_dev, GREEN, 100, 100);
	//alt_up_pixel_buffer_dma_draw_line(pixel_buf_dma_dev, 0, 0, 100, 100, GREEN, 1);
	alt_up_pixel_buffer_dma_swap_buffers(pixel_buf_dma_dev);
	while(1){};
}

/*
 * main.cpp
 *
 *  Created on: 11 apr 2022
 *      Author: 39327
 */
#include <unistd.h>
#include <stdio.h>
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

	usleep(1000);

	alt_up_pixel_buffer_dma_clear_screen(pixel_buf_dma_dev,0);
	alt_up_pixel_buffer_dma_clear_screen(pixel_buf_dma_dev,1);


	for (int i = 0; i < 220; i++)
	{
		alt_up_pixel_buffer_dma_draw_line(pixel_buf_dma_dev, i, 0, 100+i, 100, i*1000, 0);
	}
	while(1){};
}

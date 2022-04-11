/*
 * main.cpp
 *
 *  Created on: 11 apr 2022
 *      Author: 39327
 */
#include "system.h"

// define a pointer of type pixel_buffer...
// to use as a reference in the dma functions
//
alt_up_pixel_buffer_dma_dev * pixel_buf_dma_dev;


// open the Pixel Buffer port
// - command is in drivers/inc/alter...video_pixel_buffer_dma.h
// name reference is in system.h
// - "/dev/video_pixel_buffer_dma_0"
//
pixel_buf_dma_dev = alt_up_pixel_buffer_dma_open_dev ("/dev/video_pixel_buffer_dma_0");
int main(){

}

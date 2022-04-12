/*
 * main.cpp
 *
 *  Created on: 11 apr 2022
 *      Author: 39327
 */
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include "../inc/config.h"
#include "system.h"
#include "../../test_VGA1_bsp/drivers/inc/altera_up_avalon_video_pixel_buffer_dma.h"




// open the Pixel Buffer port
// - command is in drivers/inc/alter...video_pixel_buffer_dma.h
// name reference is in system.h
// - "/dev/video_pixel_buffer_dma_0"
//

alt_up_pixel_buffer_dma_dev *pixel_buf_dma_dev;

int main()
{
    pixel_buf_dma_dev = alt_up_pixel_buffer_dma_open_dev("/dev/video_pixel_buffer_dma_0");
    usleep(1000000);
    // Check for error and output to the console
    //
    if ( pixel_buf_dma_dev == NULL)
    printf ("Error: could not open pixel buffer device \n");
    else
    printf ("Opened pixel buffer device \n");

    alt_up_pixel_buffer_dma_clear_screen(pixel_buf_dma_dev,0);
    usleep(1000000);
    alt_up_pixel_buffer_dma_clear_screen(pixel_buf_dma_dev,1);
    usleep(1000000);
    alt_up_pixel_buffer_dma_draw_rectangle(pixel_buf_dma_dev, 0, 0, 25, 25, 0xFF00, 0);
    alt_up_pixel_buffer_dma_draw_rectangle(pixel_buf_dma_dev, 25, 25, 0, 0, 0X00FF, 1);

    for(;;)
    {
        usleep(1000000);
        alt_up_pixel_buffer_dma_swap_buffers(pixel_buf_dma_dev);
    }
}

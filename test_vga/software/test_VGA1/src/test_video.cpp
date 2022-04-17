/*
 * main.cpp
 *
 *  Created on: 11 apr 2022
 *      Author: vanno
 */


/*
 *	se quartus o git si permettono ancora una volta di non pusharmi quello che voglio
 *	faccio il cosplay di kaczynski lo giuro
 */

/*
 * disegna una linea animata e mostra gli fps su terminale.
 * impiega una istruzione personalizzata per pulire il back buffer senza glitchare lo schermo
 * funziona, ma è lenta (già solo disegnando una linea si arriva a 90fps max)
*/

#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include "../inc/config.h"
#include "system.h"
#include "drivers/inc/altera_up_avalon_video_pixel_buffer_dma.h"
#include <math.h>
#include "sys/alt_timestamp.h"
#include <io.h>

#define PI 3.141592654
#define TIMER_FREQ 80000000
#define DELAY 1000000

alt_up_pixel_buffer_dma_dev *pixel_buf_dma_dev;


/*
 * la stessa funzione fornita dalla HAL, ma aggiunge il numero minimo di nop tra il disegno di un pixel e l'altro
 * cos� da non avere artefatti durante la pulizia del back buffer. Le nop sono previste per tutte e due le modalit�
 * di indirizzamento, giusto per sicurezza
 *
 * DA FARE:
 * pu� meritare provare di fare le nop ogni tot pixel disegnati piuttosto che sempre, magari � possibile
 * ridurre il tempo di attesa senza comunque avere problemi.
 *
 * metterla in un file .h separato, mi ha dato  problemi a compilare se non la mettevo qua e non avevo
 * voglia di risolvere il problema -SV
 */
void alt_up_pixel_buffer_dma_clear_screen_delayed(alt_up_pixel_buffer_dma_dev *pixel_buffer, int backbuffer)
/* This function clears the screen by setting each pixel to a black color. */
{
	register unsigned int addr;
	register unsigned int limit_x, limit_y;

	/* Set up the address to start clearing from and the screen boundaries. */
	if (backbuffer == 1)
		addr = pixel_buffer->back_buffer_start_address;
	else
		addr = pixel_buffer->buffer_start_address;
	limit_x = pixel_buffer->x_resolution;
	/* In 16 and 32-bit color modes we use twice or four times more memory for the display buffer.*/
	if (pixel_buffer->color_mode == ALT_UP_16BIT_COLOR_MODE) {
		limit_x = limit_x << 1;
	} else {
		limit_x = limit_x << 2;
	}
	limit_y = pixel_buffer->y_resolution;

	if (pixel_buffer->addressing_mode == ALT_UP_PIXEL_BUFFER_XY_ADDRESS_MODE) {
		/* Clear the screen when the VGA is set up in an XY addressing mode. */
		register unsigned int x,y;
		register unsigned int offset_y;
		offset_y = pixel_buffer->y_coord_offset;

		for (y = 0; y < limit_y; y++)
		{
			for (x = 0; x < limit_x; x = x + 4)
			{
				IOWR_32DIRECT(addr, x, 0);
				asm("nop");
				asm("nop");
				asm("nop");
				asm("nop");
				asm("nop");
				asm("nop");
				asm("nop");
				asm("nop");
				asm("nop");
				asm("nop");
				asm("nop");
			}
			addr = addr + (1 << offset_y);
		}
	} else {
		/* Clear the screen when the VGA is set up in a linear addressing mode. */
		register int x;
		limit_y = limit_x*limit_y;

		for (x = 0; x < limit_y; x = x + 4)
		{
			IOWR_32DIRECT(addr, x, 0);
			asm("nop");
			asm("nop");
			asm("nop");
			asm("nop");
			asm("nop");
			asm("nop");
			asm("nop");
			asm("nop");
			asm("nop");
			asm("nop");
			asm("nop");
		}
	}
}

int main()
{

	const int center[2]{320/2, 240/2};
	const int radius{240/4};
	const int frametime_10ns ((((float)0.0167)*1000000)*100);
	int point[2][2];
	int theta{0};
	uint32_t fps;
	float arg;
	uint32_t timer{0};

    usleep(1000000);

    pixel_buf_dma_dev = alt_up_pixel_buffer_dma_open_dev("/dev/video_pixel_buffer_dma_0");

    alt_timestamp_start();

    for(;;)
    {
    	alt_up_pixel_buffer_dma_clear_screen_delayed(pixel_buf_dma_dev,1);

    	arg = (theta * PI) / 180;
    	point[0][0] = center[0] + radius*cos(arg);
    	point[0][1] = center[1] + radius*sin(arg);
    	point[1][0] = center[0] - radius*cos(arg);
    	point[1][1] = center[1] - radius*sin(arg);
    	theta++;
    	if (theta>=360){ theta = 0;}

    	alt_up_pixel_buffer_dma_draw_line(pixel_buf_dma_dev, point[0][0],point[0][1], point[1][0], point[1][1], WHITE, 1);
    	alt_up_pixel_buffer_dma_swap_buffers(pixel_buf_dma_dev);

    	fps = TIMER_FREQ/alt_timestamp();
    	printf("fps : %d\n",fps);
    	alt_timestamp_start();

    	while (alt_up_pixel_buffer_dma_check_swap_buffers_status(pixel_buf_dma_dev)){;}

    }
}

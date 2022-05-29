
#include "../inc/config.h"



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

void helper_plot_pixel_enhanced_clipping(register unsigned int buffer_start, register int line_size, register int x, register int y, register int color, register int mode)
/* This is a helper function that draws a pixel at a given location. Note that no boundary checks are made,
 * so drawing off-screen may cause unpredictable side effects. */
{
	if (mode == 0)
		IOWR_8DIRECT(buffer_start, line_size*y+x, color);
	else if (mode == 1)
		IOWR_16DIRECT(buffer_start, (line_size*y+x) << 1, color);
	else
		IOWR_32DIRECT(buffer_start, (line_size*y+x) << 2, color);
}
void alt_up_pixel_buffer_dma_draw_line_enhanced_clipping(alt_up_pixel_buffer_dma_dev *pixel_buffer, int x0, int y0, int x1, int y1, int color, int backbuffer)
/* This function draws a line between points (x0, y0) and (x1, y1). The function does not checks if it draws a pixel within screen boundaries.
 * users should ensure that the line is drawn within the screen boundaries.
 * 
 * Aggiunto il controllo per il bordo, per ora si limita a non disegnare le linee
 */
{
	register int x_0 = x0;
	register int y_0 = y0;
	register int x_1 = x1;
	register int y_1 = y1;

	//overkill per ora, utile se serve fare clipping vero e proprio
	register char x0_valid = ((x_0 >=0) && (x_0<X_RESOLUTION)) ? 1 : 0;
	register char x1_valid = ((x_1 >=0) && (x_1<X_RESOLUTION)) ? 1 : 0;
	register char y0_valid = ((y_0 >=0) && (y_0<Y_RESOLUTION)) ? 1 : 0;
	register char y1_valid = ((y_1 >=0) && (y_1<Y_RESOLUTION)) ? 1 : 0;
	register char p0_valid = x0_valid && y0_valid;
	register char p1_valid = x1_valid && y1_valid;
	register char all_valid = p0_valid && p1_valid;

	//
	if(all_valid){
		register char steep = (ABS(y_1 - y_0) > ABS(x_1 - x_0)) ? 1 : 0;
		register int deltax, deltay, error, ystep, x, y;
		register int color_mode =	(pixel_buffer->color_mode == ALT_UP_8BIT_COLOR_MODE) ? 0 :
									(pixel_buffer->color_mode == ALT_UP_16BIT_COLOR_MODE) ? 1 : 2;
		register int line_color = color;
		register unsigned int buffer_start;
		register int line_size = (pixel_buffer->addressing_mode == ALT_UP_PIXEL_BUFFER_XY_ADDRESS_MODE) ? (1 << (pixel_buffer->y_coord_offset-color_mode)) : pixel_buffer->x_resolution;

		if (backbuffer == 1)
			buffer_start = pixel_buffer->back_buffer_start_address;
		else
			buffer_start = pixel_buffer->buffer_start_address;

		/* Preprocessing inputs */
		if (steep > 0) {
			// Swap x_0 and y_0
			error = x_0;
			x_0 = y_0;
			y_0 = error;
			// Swap x_1 and y_1
			error = x_1;
			x_1 = y_1;
			y_1 = error;
		}
		if (x_0 > x_1) {
			// Swap x_0 and x_1
			error = x_0;
			x_0 = x_1;
			x_1 = error;
			// Swap y_0 and y_1
			error = y_0;
			y_0 = y_1;
			y_1 = error;
		}

		/* Setup local variables */
		deltax = x_1 - x_0;
		deltay = ABS(y_1 - y_0);
		error = -(deltax / 2); 
		y = y_0;
		if (y_0 < y_1)
			ystep = 1;
		else
			ystep = -1;

		/* Draw a line - either go along the x axis (steep = 0) or along the y axis (steep = 1). The code is replicated to
		 * compile well on low optimization levels. */
		if (steep == 1)
		{
			for (x=x_0; x <= x_1; x++) {
				helper_plot_pixel_enhanced_clipping(buffer_start, line_size, y, x, line_color, color_mode);
				error = error + deltay;
				if (error > 0) {
					y = y + ystep;
					error = error - deltax;
				}
			}
		}
		else
		{
			for (x=x_0; x <= x_1; x++) {
				helper_plot_pixel_enhanced_clipping(buffer_start, line_size, x, y, line_color, color_mode);
				error = error + deltay;
				if (error > 0) {
					y = y + ystep;
					error = error - deltax;
				}
			}
		}
	}
}



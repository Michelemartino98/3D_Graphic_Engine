
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



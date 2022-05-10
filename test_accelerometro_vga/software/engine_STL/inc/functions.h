#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "config.h"


/**
 *
 * @brief   Modificata da alt_up_pixel_buffer_dma_clear_screen, con aggiunta di NOP
 *          per permettere l'accesso alla SDRAM da parte del DMA durante i cicli di scrittura.
 *
 * @param pixel_buffer -- the pointer to the VGA structure
 * @param backbuffer -- set to 1 to clear the back buffer, otherwise set to 0 to clear the current screen.
 *
 * @return 0 if complete, 1 if still processing 
 **/
void alt_up_pixel_buffer_dma_clear_screen_delayed(alt_up_pixel_buffer_dma_dev*, int);


/**
 * @brief This function draws a line of a given color between points (x0,y0) and (x1,y1).
 *        Ora implementa un controllo per i bordi
 *
 * @param pixel_buffer -- the pointer to the VGA structure
 * @param x0,x1,y0,y1 -- coordinates (x0,y0) and (x1,y1) correspond to end points of the line
 * @param color -- color of the line to be drawn
 * @param backbuffer -- set to 1 to select the back buffer, otherwise set to 0 to select the current screen.
 *
 * @return 0 if complete, 1 if still processing 
 **/

void alt_up_pixel_buffer_dma_draw_line_enhanced_clipping(alt_up_pixel_buffer_dma_dev *pixel_buffer, int x0, int y0, int x1, int y1, int color, int backbuffer);

#endif

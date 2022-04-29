#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

//#include "config.h"


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

#endif

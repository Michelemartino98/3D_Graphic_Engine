###### dimensionamento video buffer

fine sdram è 0x03ff_ffff

dimensione singolo buffer è 320\*240\*2 = 0x0002_5800

pertanto un buffer è { 0x03ff_ffff, 0x03fd_a7ff}

e un altro a {0x03fd_a7fe, 0x03fb_47ffe}

**importante** mettere l'addressing mode _consecutive_, o altrimenti vai a sminchiare tutto

###### rimuovere glitch video in scrittura back buffer

nella definizione di _alt_up_pixel_buffer_dma_clear_screen_, nei cicli di scrittura del ciclo for, serve aggiungere 11 *nop*, scrivendole come asm("nop");
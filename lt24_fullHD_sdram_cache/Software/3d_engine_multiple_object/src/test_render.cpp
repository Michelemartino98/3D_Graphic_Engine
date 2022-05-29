 
#include "../inc/config.h" 
 
 
 
extern "C" { 
#include "touch_spi.h" 
#include "terasic_includes.h" 
#include "ILI9341.h" 
#include "simple_graphics.h" 
#include "alt_video_display.h" 
} 
 
extern int touch_pending; 
extern RECT rect_z_ctrl, rect_xy_ctrl, rect_cmd_ctrl; 
 
alt_up_pixel_buffer_dma_dev *pixel_buf_dma_dev; 
TOUCH_HANDLE *pTouch; 
 
alt_video_display Display; 
 
Graphic_engine Object_3D; 
 
uint8_t display_digit(uint8_t val){ 
	uint8_t lut[20] = {0x3F, 0x06, 0x5B, 0x4F, 	//0 to 3 
			0x66, 0x6D, 0x7D, 0x07,	//4 to 7 
			0x7F, 0x6F, 0x77, 0x7C,  //8 to B 
			0x39, 0x5E, 0x79, 0x71,  //C to F 
			0x00, 0x40, 0x5E, 0x76};	//0x00 codifica il display spento -> NO_NUMBER, 0x40 codifica il meno; 
	return (lut[val]); 
} 
void display_fps(uint32_t fps){ 
	uint8_t units, tens, hundreds; 
 
	hundreds = (fps / 100) ? (fps / 100) : NO_NUMBER ; 
	tens = (fps % 100) / 10; 
	tens = ((hundreds == NO_NUMBER) && (tens == 0)) ? NO_NUMBER : tens; 
	units = fps % 10; 
    IOWR_ALTERA_AVALON_PIO_DATA(HEX3_HEX0_BASE, display_digit(units) << FIRST_DISPLAY | display_digit(tens) << SECOND_DISPLAY | display_digit(hundreds) << THIRD_DISPLAY); 
 
} 
 
int main(){ 
 
	uint32_t fps; 
 
	 
 
	 
	pixel_buf_dma_dev = alt_up_pixel_buffer_dma_open_dev("/dev/video_pixel_buffer_dma_0"); 
 
	alt_up_pixel_buffer_dma_clear_screen_delayed(pixel_buf_dma_dev,1);	//pulisco il frame iniziale e lo mando alla vga 
	alt_up_pixel_buffer_dma_swap_buffers(pixel_buf_dma_dev); 
    while (alt_up_pixel_buffer_dma_check_swap_buffers_status(pixel_buf_dma_dev)){;} 
 
	init_accelerometer(); 
	bool accelerometer_on;  
 
	// init LCD 
	LCD_Init(); 
	LCD_Clear(0X0000); 
 
	Display.interlace = 0; 
	Display.bytes_per_pixel = 2; 
	Display.color_depth = 16; 
	Display.height = SCREEN_HEIGHT; 
	Display.width = SCREEN_WIDTH; 
 
	// init touch 
	pTouch = Touch_Init(TOUCH_SPI_BASE, TOUCH_PEN_IRQ_N_BASE, TOUCH_PEN_IRQ_N_IRQ); 
 
	 
#ifdef DEBUG_TOUCH 
	if (!pTouch){ 
		printf("Failed to init touch\r\n"); 
	}else{ 
		printf("Init touch successfully\r\n"); 
	} 
    #endif 
 
	 
	int x,y; 
	//schermata di benevenuto 
	GUI_show_welcome(); 
	while( !Touch_GetXY(pTouch,&x,&y) ) {;}
	//usleep(1000000); 
	//pulizia schermo 
	//LCD_Clear(WHITE_24); 
	// 
	GUI_desk_init(); 
	 
	alt_timestamp_start(); 
 
	for(;;){ 
		 
		accelerometer_on = LT24_controller(); 

		if( accelerometer_on ){ 
			accelerometer_controller(); 
		} 
		
		Object_3D.calculate_rendering(); 
		Object_3D.display_frame();
		Object_3D.change_object(); 
		
 
		//calcolo fps e riavvio del timer 
		fps = TIMER_FREQ/ alt_timestamp(); 
		display_fps(fps); 
		alt_timestamp_start();	
			 
 
	} 
} 
 

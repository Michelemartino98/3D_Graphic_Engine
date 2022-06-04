#include "../inc/config.h" 
  
extern "C" { 
#include "touch_spi.h" 
#include "terasic_includes.h" 
#include "ILI9341.h" 
#include "simple_graphics.h" 
#include "alt_video_display.h" 
} 
  
alt_up_pixel_buffer_dma_dev *pixel_buf_dma_dev; 
TOUCH_HANDLE *pTouch; 

alt_video_display Display; 
 
Graphic_engine Object_3D; 
 

 
int main(){ 
 
	uint32_t fps = 60; //valore di default, affinchè venga utilizzato per calcolare l'inerzia 
/////////////   init VGA   ///////////////////////// 
	pixel_buf_dma_dev = alt_up_pixel_buffer_dma_open_dev("/dev/video_pixel_buffer_dma_0"); 
	
	//pulisco il frame iniziale e lo mando alla vga

	alt_up_pixel_buffer_dma_clear_screen(pixel_buf_dma_dev,1); 
    alt_up_pixel_buffer_dma_clear_screen(pixel_buf_dma_dev,0);   


/////////////   init acelerometer /////////////////////// 
	init_accelerometer(); 

#ifdef LT24_PRESENT 
	bool accelerometer_on;  
 
/////////////   init LCD ///////////////////////
	LCD_Init(); 
	LCD_Clear(0X0000); 
 
	Display.interlace = 0; 
	Display.bytes_per_pixel = 2; 
	Display.color_depth = 16; 
	Display.height = SCREEN_HEIGHT; 
	Display.width = SCREEN_WIDTH; 

/////////////// init touch /////////////
	pTouch = Touch_Init(TOUCH_SPI_BASE, TOUCH_PEN_IRQ_N_BASE, TOUCH_PEN_IRQ_N_IRQ); 	 
#ifdef DEBUG_TOUCH 
	if (!pTouch){ 
		printf("Failed to init touch\r\n"); 
	}else{ 
		printf("Init touch successfully\r\n"); 
	} 
    #endif 
	

	//schermata di benvenuto 
	GUI_show_welcome(); 
	int x,y; 
	//while( !Touch_GetXY(pTouch,&x,&y) ) {;}

	GUI_desk_init(); 
#endif

	Object_3D.init_object();

	alt_timestamp_start(); 

	for(;;){ 

#ifdef LT24_PRESENT 		 
		accelerometer_on = LT24_controller(fps); 

		if( accelerometer_on ){ 
			accelerometer_controller(); 
		} 
#else		
		accelerometer_controller(); 
#endif
		Object_3D.calculate_rendering();
		
		Object_3D.display_frame(); 

		//calcolo fps e riavvio del timer 
		fps = TIMER_FREQ/ alt_timestamp(); 
		display_fps(fps); 
		alt_timestamp_start();

		Object_3D.change_object(); 	
 
	} 
} 
 

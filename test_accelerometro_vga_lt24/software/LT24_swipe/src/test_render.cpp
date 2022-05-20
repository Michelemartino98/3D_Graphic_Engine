
#include "../inc/config.h"



extern "C" {
#include "touch_spi.h"
#include "terasic_includes.h"
#include "ILI9341.h"
#include "simple_graphics.h"
#include "alt_video_display.h"
}

alt_up_pixel_buffer_dma_dev *pixel_buf_dma_dev;

alt_video_display Display;

Cube_3D Cube;

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
	HEX3_HEX0_DATA_REG = display_digit(units) << FIRST_DISPLAY | display_digit(tens) << SECOND_DISPLAY | display_digit(hundreds) << THIRD_DISPLAY ;

}

int main(){

	uint32_t fps;
	uint32_t delta_for_fps;

	init_accelerometer();
	pixel_buf_dma_dev = alt_up_pixel_buffer_dma_open_dev("/dev/video_pixel_buffer_dma_0");
	

	TOUCH_HANDLE *pTouch;

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
	//stringhe per disegnare su LT24 
	char *cmd_str[] = {"ROT" , "TRASL" , "SCALE"} ;
	//flag di controllo : se false disabilita i comandi 
	bool run_touch{FALSE};
#ifdef DEBUG_TOUCH
	if (!pTouch){
		printf("Failed to init touch\r\n");
	}else{
		printf("Init touch successfully\r\n");
	}
    #endif


	GUI_show_welcome();
	usleep(1000000);
	LCD_Clear(WHITE_24);

	RECT rect_z_ctrl, rect_xy_ctrl, rect_cmd_ctrl;
	POINT pt;
	SWIPE touch_swipe = {
			.delta_x = 0,
			.delta_y = 0,
			.delta_t = 0,
			.previous_x = 0,
			.previous_y = 0,
			.current_x = 0,
			.current_y = 0,
			.point_valid = FALSE,
			.end_of_swipe = TRUE,

	};

	cmd_t actual_cmd = ROT;
	int x_touch,y_touch;		//uscita row del touch, da trasformare
	//inizializza le strutture dei rettangoli e li disegna
	GUI_desk_init(&rect_xy_ctrl, &rect_z_ctrl, &rect_cmd_ctrl);
	
	alt_timestamp_start();
	delta_for_fps = alt_timestamp();
	//variabili per fare lo swipe


	for(;;){
		
		if (Touch_GetXY(pTouch, &x_touch, &y_touch)){
			pt.x = x_touch;//y_touch;   	LA TRASLAZIONE VIENE EFFETTUATA DIRETTAMENTE ALL'
			pt.y = y_touch;//240 - x_touch; INTERNO DELLA FUNZIONE GET_XY
			#ifdef DEBUG_TOUCH
			printf("x=%d, y=%d\r\n", pt.x,pt.y);
			#endif
			
			if(is_point_in_rect(&pt,&rect_cmd_ctrl)){ //sono nell'area di controllo dei comandi
				if(!run_touch){
					run_touch = true;	//creo un latch per il semaforo
					vid_print_string( (rect_cmd_ctrl.right)/2 , rect_cmd_ctrl.bottom/2 , WHITE_24, cour10_font, &Display, "PRESS TO INIT" );
				}
				vid_print_string( (rect_cmd_ctrl.right)/2 , rect_cmd_ctrl.bottom/2 , WHITE_24, cour10_font, &Display, cmd_str[actual_cmd]);
				actual_cmd = (actual_cmd >= 2) ? 0 : (actual_cmd+1);

				#ifdef DEBUG_TOUCH
				printf("command: %d\n", actual_cmd);
				#endif
				vid_print_string( (rect_cmd_ctrl.right)/2 , rect_cmd_ctrl.bottom/2 , GREEN_24, cour10_font, &Display, cmd_str[actual_cmd]);
				usleep(800000);	//ritardo per evitare che pressioni prolungate facciano cambiare più comandi
				Touch_EmptyFifo(pTouch);		//svuoto la FIFO
			}
			else if(is_point_in_rect(&pt,&rect_z_ctrl) && run_touch){ //sono nell'are di controllo z
				printf("Z area\r\n");

			}
			else if(is_point_in_rect(&pt,&rect_xy_ctrl) && run_touch){	//sono nell'are di controllo xy
				printf("XY area\r\n\n");
				evaluate_swipe(pTouch, &touch_swipe,delta_for_fps);

			}
			
		}

		accelerometer_controller();
		Cube.calculate_rendering();
		Cube.display_frame();

// s non riavvio maii il timer ci sta che quando va in overflow succedono cose strane
		fps = TIMER_FREQ/ (alt_timestamp() - delta_for_fps);
		delta_for_fps = alt_timestamp();
		display_fps(fps);
		//alt_timestamp_start();		// tolto visto che non si riavvia il timer

	}
}


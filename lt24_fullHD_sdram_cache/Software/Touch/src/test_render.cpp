
#include "../inc/config.h"



extern "C" {
#include "touch_spi.h"
#include "terasic_includes.h"
#include "ILI9341.h"
#include "simple_graphics.h"
#include "alt_video_display.h"
}

extern int touch_pending;

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
	POINT previous_pt;
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

		alt_irq_disable(TOUCH_PEN_IRQ_N_IRQ);  //va di pari passo con la disabilitazione dentro l'isr
		Touch_GetXY(pTouch, &x_touch, &y_touch);

		previous_pt.x = pt.x;
		previous_pt.y = pt.y;

		pt.x = x_touch;//y_touch;   	LA TRASLAZIONE VIENE EFFETTUATA DIRETTAMENTE ALL'
		pt.y = y_touch;//240 - x_touch; INTERNO DELLA FUNZIONE GET_XY

		evaluate_swipe(pTouch, &touch_swipe, &pt, delta_for_fps);
		alt_irq_enable(TOUCH_PEN_IRQ_N_IRQ);
		#ifdef DEBUG_TOUCH
		printf("x=%d, y=%d\r\n", pt.x,pt.y);
		#endif
		
		if(is_point_in_rect(&pt,&rect_cmd_ctrl) && (previous_pt.x!=pt.x) && (previous_pt.y!=pt.y)){ //sono nell'area di controllo dei comandi per la prima volta
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
			usleep(800000);	//ritardo per evitare che pressioni prolungate facciano cambiare pi� comandi
			Touch_EmptyFifo(pTouch);		//svuoto la FIFO
		}
		else if(is_point_in_rect(&pt,&rect_z_ctrl) && run_touch){ //sono nell'are di controllo z
			#ifdef DEBUG_TOUCH
				printf("Z area\r\n");
			#endif
			if( touch_swipe.point_valid == true || touch_swipe.end_of_swipe ) {
				if( actual_cmd == TRASL ){
						if( touch_swipe.end_of_swipe ){
							//inerzia su y
							if( touch_swipe.delta_y > 0 ){
								touch_swipe.delta_y = (touch_swipe.delta_y-TRASL_INERTIA < 0) ? 0 : touch_swipe.delta_y - TRASL_INERTIA ;
								}
							else if ( touch_swipe.delta_y < 0 ){
								touch_swipe.delta_y = (touch_swipe.delta_y+TRASL_INERTIA > 0) ? 0 : touch_swipe.delta_y + TRASL_INERTIA ;
							}
						}
					Cube.update_translation_relative( touch_swipe.delta_y/ATTENUATION_FACTOR_TRASL , Z );
				}
				else if ( actual_cmd == SCALE ){
					Cube.update_scaling_relative(touch_swipe.delta_y/ATTENUATION_FACTOR_SCALE , Z );
					touch_swipe.delta_x = 0; //scala senza inerzia quindi una volta fatto l incremento metto il delta a zero 
					touch_swipe.delta_y = 0;
				}
			}
		}
		else if(is_point_in_rect(&pt,&rect_xy_ctrl) && run_touch){	//sono nell'are di controllo xy
			#ifdef DEBUG_TOUCH
				printf("XY area\r\n\n");
			#endif
						
			if( touch_swipe.point_valid == true || touch_swipe.end_of_swipe ) {
				if( actual_cmd == ROT ){
					if( touch_swipe.end_of_swipe ){
						//inerzia su x
						if( touch_swipe.delta_x > 0 ){
							touch_swipe.delta_x = touch_swipe.delta_x-ROT_INERTIA < 0 ? 0 : touch_swipe.delta_x - ROT_INERTIA ;
							}
						else if ( touch_swipe.delta_x < 0 ){
							touch_swipe.delta_x = touch_swipe.delta_x+ROT_INERTIA > 0 ? 0 : touch_swipe.delta_x + ROT_INERTIA ;
						}
						//inerzia su y
						if( touch_swipe.delta_y > 0 ){
							touch_swipe.delta_y = touch_swipe.delta_y-ROT_INERTIA < 0 ? 0 : touch_swipe.delta_y - ROT_INERTIA ;
							}
						else if ( touch_swipe.delta_y < 0 ){
							touch_swipe.delta_y = touch_swipe.delta_y+ROT_INERTIA > 0 ? 0 : touch_swipe.delta_y + ROT_INERTIA ;
						}
					}
					Cube.update_rotation_relative( touch_swipe.delta_x/ATTENUATION_FACTOR_ROT , Y);
					Cube.update_rotation_relative( touch_swipe.delta_y/ATTENUATION_FACTOR_ROT , X);
				}
				else if ( actual_cmd == TRASL ){
					if( touch_swipe.end_of_swipe ){
						//inerzia su x
						if( touch_swipe.delta_x > 0 ){
							touch_swipe.delta_x = touch_swipe.delta_x-TRASL_INERTIA < 0 ? 0 : touch_swipe.delta_x - TRASL_INERTIA ;
							}
						else if ( touch_swipe.delta_x < 0 ){
							touch_swipe.delta_x = touch_swipe.delta_x+TRASL_INERTIA > 0 ? 0 : touch_swipe.delta_x + TRASL_INERTIA ;
						}
						//inerzia su y
						if( touch_swipe.delta_y > 0 ){
							touch_swipe.delta_y = touch_swipe.delta_y-TRASL_INERTIA < 0 ? 0 : touch_swipe.delta_y - TRASL_INERTIA ;
							}
						else if ( touch_swipe.delta_y < 0 ){
							touch_swipe.delta_y = touch_swipe.delta_y+TRASL_INERTIA > 0 ? 0 : touch_swipe.delta_y + TRASL_INERTIA ;
						}
					}
					Cube.update_translation_relative(touch_swipe.delta_x/ATTENUATION_FACTOR_TRASL , X); 
					Cube.update_translation_relative(-touch_swipe.delta_y/ATTENUATION_FACTOR_TRASL , Y);//'-' per avere la traslazione nella direzione concorde alla direzione della swipe 
				}
				else{
					Cube.update_scaling_relative( touch_swipe.delta_x/ATTENUATION_FACTOR_SCALE , Y );
					Cube.update_scaling_relative( touch_swipe.delta_y/ATTENUATION_FACTOR_SCALE , X );
					touch_swipe.delta_x = 0; //scala senza inerzia quindi una volta fatto l incremento metto il delta a zero 
					touch_swipe.delta_y = 0;
				}

			}
		}
		//else{
		//	touch_pending = FALSE;
		//	printf("touch pending FALSE\n");
		//}

		if(IORD_ALTERA_AVALON_PIO_DATA(SLIDERS_BASE)&BIT(5)){
			accelerometer_controller();
		}
		Cube.calculate_rendering();
		Cube.display_frame();

// s non riavvio maii il timer ci sta che quando va in overflow succedono cose strane
		fps = TIMER_FREQ/ (alt_timestamp() - delta_for_fps);
		delta_for_fps = alt_timestamp();
		display_fps(fps);
		//alt_timestamp_start();		// tolto visto che non si riavvia il timer

	}
}

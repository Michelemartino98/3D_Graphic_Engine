extern "C" {
#include "touch_spi.h"
#include "terasic_includes.h"
#include "ILI9341.h"
#include "simple_graphics.h"
#include "alt_video_display.h"

#include "simple_text.h"
#include "fonts.h"
}
#include "config.h"

extern alt_video_display Display;
extern Graphic_engine Object_3D;
extern TOUCH_HANDLE pTouch;

RECT rect_z_ctrl, rect_xy_ctrl, rect_cmd_ctrl, rect_acc_ctrl, rect_reset;

void GUI_show_welcome(){
	int x, y;

    LCD_Clear(WHITE_24);
	usleep(10000);
	x = Display.width / 2 - 80;
	y = Display.height / 2 - 100;

	//vid_print_string(x, y,    GREEN_24, cour10_font, &Display, "3D GRAPHIC ENGINE");
	vid_print_string_alpha(x, y,    BLACK_16, WHITE_16, tahomabold_20, &Display, "3D GRAPHIC ENGINE");
	//vid_print_string(x, y+22, GREEN_24, cour10_font, &Display, "by");
	vid_print_string_alpha(Display.width / 2, y+40,    BLACK_16, WHITE_16, tahomabold_20, &Display, "by");
    //vid_print_string(x, y+44, GREEN_24, cour10_font, &Display, "Martino, Vannoni, Zocco");
	vid_print_string_alpha(x-10, y+80,    GREEN_16, WHITE_16, tahomabold_20, &Display,"Martino, Vannoni, Zocco");
}

void GUI_desk_init(){

	LCD_Clear(WHITE_24);
    //box per controllo z
    rect_z_ctrl.left = 0;
	rect_z_ctrl.top = 40;
	rect_z_ctrl.right = 80;
	rect_z_ctrl.bottom = 240;

	//box per controllo comandi (S,T,R)
    rect_cmd_ctrl.left = 0;
	rect_cmd_ctrl.top = 0;
	rect_cmd_ctrl.right = 239;
	rect_cmd_ctrl.bottom = 39;//stesso discorso di 80 + 1

	//box per resettare le trasformazioni
	rect_reset.left = 240; 
	rect_reset.top =  0;
	rect_reset.right = 279;
	rect_reset.bottom = 39;

	//box per controllo acc
	rect_acc_ctrl.left = 280; 
	rect_acc_ctrl.top =  0;
	rect_acc_ctrl.right = 320;
	rect_acc_ctrl.bottom = 39;

    //box per controllo xy
    rect_xy_ctrl.left = 81; //80 + 1 per evitare la sovrapposizione dei bordi dei rettangoli
	rect_xy_ctrl.top = 40; 
	rect_xy_ctrl.right = 320;
	rect_xy_ctrl.bottom = 240;
	
    

	//disegno i box dell'intefaccia
	vid_draw_box( rect_xy_ctrl.left,rect_xy_ctrl.top,rect_xy_ctrl.right,rect_xy_ctrl.bottom, ORANGE_24, 0, &Display );
    vid_draw_box( rect_z_ctrl.left,rect_z_ctrl.top,rect_z_ctrl.right,rect_z_ctrl.bottom, VIOLET_24, 0, &Display );
    vid_draw_box( rect_cmd_ctrl.left,rect_cmd_ctrl.top,rect_cmd_ctrl.right,rect_cmd_ctrl.bottom, BLUE_24, 0, &Display );
	vid_draw_box( rect_reset.left,rect_reset.top,rect_reset.right,rect_reset.bottom, ORANGE_24, 1, &Display );
	vid_draw_box( rect_acc_ctrl.left,rect_acc_ctrl.top,rect_acc_ctrl.right,rect_acc_ctrl.bottom, RED_24, 1, &Display );

	vid_print_string( (rect_cmd_ctrl.right)/2 - OFFSET*5  , rect_cmd_ctrl.bottom/2 , GREEN_24, cour10_font, &Display, "Command =");
	vid_print_string( (rect_cmd_ctrl.right)/2 - OFFSET  , rect_cmd_ctrl.bottom/2 , GREEN_24, cour10_font, &Display, "ROT");
	vid_print_string( rect_z_ctrl.right/2 - OFFSET , rect_xy_ctrl.top + OFFSET , GREEN_24, cour10_font, &Display, "Z ctrl");
	vid_print_string( rect_cmd_ctrl.right/2 + OFFSET , rect_xy_ctrl.top + OFFSET , GREEN_24, cour10_font, &Display, "XY ctrl");
	vid_print_string( rect_reset.left + 10  , rect_reset.bottom - 15 , BLACK_24, cour10_font, &Display, "RST");
	vid_print_string( rect_acc_ctrl.left + 10  , rect_acc_ctrl.bottom - 15 , BLACK_24, cour10_font, &Display, "ACC");


}

bool is_point_in_rect(POINT *pt, RECT *rc){ //valuta in quale box è avvenuto il tocco
    bool bYes = FALSE;
    
    if (pt->x >= rc->left && pt->x <= rc->right && pt->y >= rc->top && pt->y <= rc->bottom)
        bYes = TRUE;
    
    return bYes;
}

bool LT24_controller(uint32_t fps){
	////////////////  dati per valutare il tocco/////////////////
	static bool accelerometer_on = FALSE;
	static POINT pt;
	static POINT previous_pt;
	static SWIPE touch_swipe = {
			.delta_x = 0,
			.delta_y = 0,
			.previous_x = 0,
			.previous_y = 0,
			.current_x = 0,
			.current_y = 0,
			.point_valid = FALSE,
			.end_of_swipe = TRUE,
			.first_touch = FALSE,
	};
	char *cmd_str[] = {"ROT" , "TRASL" , "SCALE"} ;
	static cmd_t actual_cmd = ROT;
	static int x_touch,y_touch;		

	///////////acquisizione del punto 
		alt_irq_disable(TOUCH_PEN_IRQ_N_IRQ);  //va di pari passo con la disabilitazione dentro l'isr
		Touch_GetXY(pTouch, &x_touch, &y_touch);

		previous_pt.x = pt.x;
		previous_pt.y = pt.y;

		pt.x = x_touch; 
		pt.y = y_touch; 

		evaluate_swipe(pTouch, &touch_swipe, &pt);
		alt_irq_enable(TOUCH_PEN_IRQ_N_IRQ);
		#ifdef DEBUG_TOUCH
		printf("x=%d, y=%d\r\n", pt.x,pt.y);
		#endif

//------------------------sono nell'area di controllo dei comandi ---------------------------------------------
		if(is_point_in_rect(&pt,&rect_cmd_ctrl) \		 
			&& (previous_pt.x!=pt.x) \
			&& (previous_pt.y!=pt.y)  \
			&& touch_swipe.first_touch == TRUE){ 	 // evito che uno swipe troppo lungo mi faccia commutare il comando
			
			vid_print_string( rect_cmd_ctrl.right/2 - OFFSET , rect_cmd_ctrl.bottom/2 , WHITE_24, cour10_font, &Display, cmd_str[actual_cmd]);
			actual_cmd = (actual_cmd >= 2) ? 0 : (actual_cmd + 1);
			vid_print_string( (rect_cmd_ctrl.right)/2 - OFFSET  , rect_cmd_ctrl.bottom/2 , GREEN_24, cour10_font, &Display,  cmd_str[actual_cmd]);
			#ifdef DEBUG_TOUCH
			printf("command: %d\n", actual_cmd);
			#endif
			usleep(400000);	//ritardo per evitare che pressioni prolungate facciano cambiare pi� comandi
			Touch_EmptyFifo(pTouch);		//svuoto la FIFO
		}
		
//------------------------------- sono nell'are di controllo Z  -------------------------------------------------------
		else if(is_point_in_rect(&pt,&rect_z_ctrl)){ 
			#ifdef DEBUG_TOUCH
				printf("Z area\r\n");
			#endif
			if( touch_swipe.point_valid == true || touch_swipe.end_of_swipe ) {
				if( actual_cmd == TRASL ){
						if( touch_swipe.end_of_swipe ){
							//inerzia su y
							if( touch_swipe.delta_y > 0 ){
								touch_swipe.delta_y = (touch_swipe.delta_y-trasl_inertia(fps) < 0) ? 0 : touch_swipe.delta_y - trasl_inertia(fps) ;
								}
							else if ( touch_swipe.delta_y < 0 ){
								touch_swipe.delta_y = (touch_swipe.delta_y+trasl_inertia(fps) > 0) ? 0 : touch_swipe.delta_y + trasl_inertia(fps) ;
							}
						}
					Object_3D.update_translation_relative( touch_swipe.delta_y/ATTENUATION_FACTOR_TRASL , Z );
				}
				else if ( actual_cmd == SCALE ){
					Object_3D.update_scaling_relative(touch_swipe.delta_y/ATTENUATION_FACTOR_SCALE , Z );
					touch_swipe.delta_x = 0; //scala senza inerzia quindi una volta fatto l incremento metto il delta a zero 
					touch_swipe.delta_y = 0;
				}
			}
		}
//-------------------- sono nell'are di controllo xy -------------------------------------------
		else if(is_point_in_rect(&pt,&rect_xy_ctrl)){	
			#ifdef DEBUG_TOUCH
				printf("XY area\r\n\n");
			#endif
						
			if( touch_swipe.point_valid == true || touch_swipe.end_of_swipe ) {
				if( actual_cmd == ROT ){
					if( touch_swipe.end_of_swipe ){
						//inerzia su x
						if( touch_swipe.delta_x > 0 ){
							touch_swipe.delta_x = touch_swipe.delta_x-rot_inertia(fps) < 0 ? 0 : touch_swipe.delta_x - rot_inertia(fps) ;
							}
						else if ( touch_swipe.delta_x < 0 ){
							touch_swipe.delta_x = touch_swipe.delta_x+rot_inertia(fps) > 0 ? 0 : touch_swipe.delta_x + rot_inertia(fps) ;
						}
						//inerzia su y
						if( touch_swipe.delta_y > 0 ){
							touch_swipe.delta_y = touch_swipe.delta_y-rot_inertia(fps) < 0 ? 0 : touch_swipe.delta_y - rot_inertia(fps) ;
							}
						else if ( touch_swipe.delta_y < 0 ){
							touch_swipe.delta_y = touch_swipe.delta_y+rot_inertia(fps) > 0 ? 0 : touch_swipe.delta_y + rot_inertia(fps) ;
						}
					}
					Object_3D.update_rotation_relative( touch_swipe.delta_x/ATTENUATION_FACTOR_ROT , Y);
					Object_3D.update_rotation_relative( touch_swipe.delta_y/ATTENUATION_FACTOR_ROT , X);
				}
				else if ( actual_cmd == TRASL ){
					if( touch_swipe.end_of_swipe ){
						//inerzia su x
						if( touch_swipe.delta_x > 0 ){
							touch_swipe.delta_x = touch_swipe.delta_x-trasl_inertia(fps) < 0 ? 0 : touch_swipe.delta_x - trasl_inertia(fps) ;
							}
						else if ( touch_swipe.delta_x < 0 ){
							touch_swipe.delta_x = touch_swipe.delta_x+trasl_inertia(fps) > 0 ? 0 : touch_swipe.delta_x + trasl_inertia(fps) ;
						}
						//inerzia su y
						if( touch_swipe.delta_y > 0 ){
							touch_swipe.delta_y = touch_swipe.delta_y-trasl_inertia(fps) < 0 ? 0 : touch_swipe.delta_y - trasl_inertia(fps) ;
							}
						else if ( touch_swipe.delta_y < 0 ){
							touch_swipe.delta_y = touch_swipe.delta_y+trasl_inertia(fps) > 0 ? 0 : touch_swipe.delta_y + trasl_inertia(fps) ;
						}
					}
					Object_3D.update_translation_relative(touch_swipe.delta_x/ATTENUATION_FACTOR_TRASL , X); 
					Object_3D.update_translation_relative(-touch_swipe.delta_y/ATTENUATION_FACTOR_TRASL , Y);//'-' per avere la traslazione nella direzione concorde alla direzione della swipe 
				}
				else{
					Object_3D.update_scaling_relative( touch_swipe.delta_x/ATTENUATION_FACTOR_SCALE , Y );
					Object_3D.update_scaling_relative( touch_swipe.delta_y/ATTENUATION_FACTOR_SCALE , X );
					touch_swipe.delta_x = 0; //scala senza inerzia quindi una volta fatto l incremento metto il delta a zero 
					touch_swipe.delta_y = 0;
				}

			}
		}

//------------------sono nell'area di controllo dell'accelerometro---------------------------
		if(is_point_in_rect(&pt,&rect_acc_ctrl) \		
			&& (previous_pt.x!=pt.x) \
			&& (previous_pt.y!=pt.y)  \
			&& touch_swipe.first_touch == TRUE){ 	  // evito che uno swipe troppo lungo mi faccia commutare il comando
			if(accelerometer_on){
				accelerometer_on = FALSE;
				//box rosso
				vid_draw_box( rect_acc_ctrl.left,rect_acc_ctrl.top,rect_acc_ctrl.right,rect_acc_ctrl.bottom, RED_24, 1, &Display );
				vid_print_string( rect_acc_ctrl.left + 10  , rect_acc_ctrl.bottom - 20 , BLACK_24, cour10_font, &Display, "ACC");
			}
			else{
				accelerometer_on = TRUE;
				//box verde
				vid_draw_box( rect_acc_ctrl.left,rect_acc_ctrl.top,rect_acc_ctrl.right,rect_acc_ctrl.bottom, GREEN_24, 1, &Display );
				vid_print_string( rect_acc_ctrl.left + 10  , rect_acc_ctrl.bottom - 20 , BLACK_24, cour10_font, &Display, "ACC");

			}
			
			usleep(400000);	//ritardo per evitare che pressioni prolungate facciano commutare più volte
			Touch_EmptyFifo(pTouch);		//svuoto la FIFO
		}
// --------------------------- sono nell'area del reset ---------------------------------------------------
		if(is_point_in_rect(&pt,&rect_reset) \		
					&& (previous_pt.x!=pt.x) \
					&& (previous_pt.y!=pt.y)  \
					&& touch_swipe.first_touch == TRUE){ 	  // evito che uno swipe troppo lungo mi faccia commutare il comando
			
			Object_3D.update_rotation(0,0,0);
			Object_3D.update_scaling(0.4,0.4,0.4);
			Object_3D.update_translation(0,0,-3);
			Object_3D.calculate_rendering(); 
			Object_3D.display_frame();

			//usleep(400000);	//il ritardo si può anche evitare che tanto c'è il rendering che impiega tempo
			Touch_EmptyFifo(pTouch);		//svuoto la FIFO
		}

		return accelerometer_on;	
}

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



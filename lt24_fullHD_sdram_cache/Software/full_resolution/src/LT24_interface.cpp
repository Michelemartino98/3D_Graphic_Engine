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
extern Cube_3D Cube;
extern TOUCH_HANDLE pTouch;

RECT rect_z_ctrl, rect_xy_ctrl, rect_cmd_ctrl, rect_acc_ctrl;

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
	
    //box per controllo comandi (S,T,R)
    rect_cmd_ctrl.left = 0;
	rect_cmd_ctrl.top = 0;
	rect_cmd_ctrl.right = 279;
	rect_cmd_ctrl.bottom = 39;//stesso discorso di 80 + 1

	
	vid_draw_box( rect_xy_ctrl.left,rect_xy_ctrl.top,rect_xy_ctrl.right,rect_xy_ctrl.bottom, ORANGE_24, 0, &Display );
    vid_draw_box( rect_z_ctrl.left,rect_z_ctrl.top,rect_z_ctrl.right,rect_z_ctrl.bottom, VIOLET_24, 0, &Display );
    vid_draw_box( rect_cmd_ctrl.left,rect_cmd_ctrl.top,rect_cmd_ctrl.right,rect_cmd_ctrl.bottom, BLUE_24, 0, &Display );
	vid_draw_box( rect_acc_ctrl.left,rect_acc_ctrl.top,rect_acc_ctrl.right,rect_acc_ctrl.bottom, RED_24, 1, &Display );

	vid_print_string( (rect_cmd_ctrl.right)/2 - OFFSET*5  , rect_cmd_ctrl.bottom/2 , GREEN_24, cour10_font, &Display, "Command =");
	vid_print_string( (rect_cmd_ctrl.right)/2 - OFFSET  , rect_cmd_ctrl.bottom/2 , GREEN_24, cour10_font, &Display, "ROT");
	vid_print_string( rect_z_ctrl.right/2 - OFFSET , rect_xy_ctrl.top + OFFSET , GREEN_24, cour10_font, &Display, "Z ctrl");
	vid_print_string( rect_cmd_ctrl.right/2 + OFFSET , rect_xy_ctrl.top + OFFSET , GREEN_24, cour10_font, &Display, "XY ctrl");
	vid_print_string( rect_cmd_ctrl.right + 10  , rect_cmd_ctrl.bottom/2 - 5 , BLACK_24, cour10_font, &Display, "ACC");


}

bool is_point_in_rect(POINT *pt, RECT *rc){ //valuta in quale box è avvenuto il tocco
    bool bYes = FALSE;
    
    if (pt->x >= rc->left && pt->x <= rc->right && pt->y >= rc->top && pt->y <= rc->bottom)
        bYes = TRUE;
    
    return bYes;
}

bool LT24_controller(){
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
	static int x_touch,y_touch;		//uscita row del touch, da trasformare

	//inizializza le strutture dei rettangoli e li disegna

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

		//sono nell'area di controllo dei comandi
		if(is_point_in_rect(&pt,&rect_cmd_ctrl) \		 
			&& (previous_pt.x!=pt.x) \
			&& (previous_pt.y!=pt.y)  \
			&& touch_swipe.first_touch == TRUE){ 	 // evito che uno swipe troppo lungo mi faccia commutare il comando
			
			vid_print_string( rect_cmd_ctrl.right/2 - OFFSET , rect_cmd_ctrl.bottom/2 , WHITE_24, cour10_font, &Display, cmd_str[actual_cmd]);
			actual_cmd = (actual_cmd >= 2) ? 0 : (actual_cmd+1);
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

//------------------sono nell'area di controllo dell'accelerometro---------------------------
		if(is_point_in_rect(&pt,&rect_acc_ctrl) \		
			&& (previous_pt.x!=pt.x) \
			&& (previous_pt.y!=pt.y)  \
			&& touch_swipe.first_touch == TRUE){ 	  // evito che uno swipe troppo lungo mi faccia commutare il comando
			if(accelerometer_on){
				accelerometer_on = FALSE;
				vid_draw_box( rect_acc_ctrl.left,rect_acc_ctrl.top,rect_acc_ctrl.right,rect_acc_ctrl.bottom, RED_24, 1, &Display );
				vid_print_string( rect_cmd_ctrl.right + 10  , rect_cmd_ctrl.bottom/2 - 5 , BLACK_24, cour10_font, &Display, "ACC");
			}
			else{
				accelerometer_on = TRUE;
				vid_draw_box( rect_acc_ctrl.left,rect_acc_ctrl.top,rect_acc_ctrl.right,rect_acc_ctrl.bottom, GREEN_24, 1, &Display );
				vid_print_string( rect_cmd_ctrl.right + 10  , rect_cmd_ctrl.bottom/2 - 5 , BLACK_24, cour10_font, &Display, "ACC");
			
				//disegna verde
			}
			
			usleep(400000);	//ritardo per evitare che pressioni prolungate facciano commutare più volte
			Touch_EmptyFifo(pTouch);		//svuoto la FIFO
		}

		return accelerometer_on;
		
}


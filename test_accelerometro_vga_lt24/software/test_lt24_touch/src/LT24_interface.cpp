extern "C" {
#include "touch_spi.h"
#include "terasic_includes.h"
#include "ILI9341.h"
#include "simple_graphics.h"
#include "alt_video_display.h"
}
#include "config.h"

extern alt_video_display Display;

#define SWIPE_MINIMUM_POINT 8
#define MAX_DISTANCE_BETWEEN_POINT XXX

void GUI_show_welcome(){
	int x, y;

    LCD_Clear(WHITE_24);
	x = Display.width / 2 - 60;
	y = Display.height / 2 - 40;

	vid_print_string(x, y,    GREEN_24, cour10_font, &Display, "3D GRAPHIC ENGINE");
	vid_print_string(x, y+22, GREEN_24, cour10_font, &Display, "by");
    vid_print_string(x, y+44, GREEN_24, cour10_font, &Display, "Martino, Vannoni, Zocco");
}

void GUI_desk_init( RECT *rect_xy_ctrl, RECT *rect_z_ctrl, RECT *rect_cmd_ctrl){

    //box per controllo z
    rect_z_ctrl->left = 0;
	rect_z_ctrl->top = 40;
	rect_z_ctrl->right = 80;
	rect_z_ctrl->bottom = 240;
    //box per controllo xy
    rect_xy_ctrl->left = 81; //80 + 1 per evitare la sovrapposizione dei bordi dei rettangoli
	rect_xy_ctrl->top = 40; 
	rect_xy_ctrl->right = 320;
	rect_xy_ctrl->bottom = 240;
    //box per controllo comandi (S,T,R)
    rect_cmd_ctrl->left = 0;
	rect_cmd_ctrl->top = 0;
	rect_cmd_ctrl->right = 320;
	rect_cmd_ctrl->bottom = 39;//stesso discorso di 80 + 1

	vid_draw_box(rect_xy_ctrl->left,rect_xy_ctrl->top,rect_xy_ctrl->right,rect_xy_ctrl->bottom, RED_24, 0, &Display );
    vid_draw_box(rect_z_ctrl->left,rect_z_ctrl->top,rect_z_ctrl->right,rect_z_ctrl->bottom, GREEN_24, 0, &Display );
    vid_draw_box(rect_cmd_ctrl->left,rect_cmd_ctrl->top,rect_cmd_ctrl->right,rect_cmd_ctrl->bottom, BLUE_24, 0, &Display );
	vid_print_string( rect_cmd_ctrl->right/2 , rect_cmd_ctrl->bottom/2 , GREEN_24, cour10_font, &Display, "PRESS TO INIT");
}

bool is_point_in_rect(POINT *pt, RECT *rc){ //valuta in quale box è avvenuto il tocco
    bool bYes = FALSE;
    
    if (pt->x >= rc->left && pt->x <= rc->right && pt->y >= rc->top && pt->y <= rc->bottom)
        bYes = TRUE;
    
    return bYes;
}

bool evaluate_swipe(TOUCH_HANDLE pHandle, SWIPE *touch_swipe){
	bool swipe_ok = false;
	int my_fifo[2*SWIPE_MINIMUM_POINT];
	int x,y;
	// TERASIC_TOUCH_PANEL *p = (TERASIC_TOUCH_PANEL *)pHandle;

	// if (p->fifo_front - p->fifo_rear < SWIPE_MINIMUM_POINT){ 
    //     // non abbastanza punti per calcolare lo swipe
    // 	return FALSE;
    // }

	for( int i=0; i<SWIPE_MINIMUM_POINT; i++ ){
		if(Touch_GetXY(pHandle, &x, &y)){
		my_fifo[i*2]=x;
		my_fifo[i*2+1]=y;
		printf("x,y: %d,  %d\n", my_fifo[i*2] , my_fifo[i*2+1]);
		}
		else
			printf("empty\n");
	}
	swipe_ok = true;

	return swipe_ok;
}


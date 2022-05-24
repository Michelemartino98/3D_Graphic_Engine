#ifndef LT24_INTERFACE_H_
#define LT24_INTERFACE_H_

#include "config.h"
extern "C" {
#include "touch_spi.h"
//#include "terasic_includes.h"
#include "ILI9341.h"
#include "simple_graphics.h"
#include "alt_video_display.h"
}

#define OFFSET 20

typedef struct{
    int left;
    int right;
    int top;
    int bottom;
}RECT;



void GUI_show_welcome();
void GUI_desk_init();
bool is_point_in_rect(POINT *, RECT *);
void LT24_controller();




#endif 

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

typedef struct{
    int left;
    int right;
    int top;
    int bottom;
}RECT;

typedef struct{
    int x;
    int y;
}POINT;

typedef struct{
    int delta_x;
    int delta_y;
}SWIPE;

void GUI_show_welcome();
void GUI_desk_init( RECT *, RECT *, RECT *);
bool is_point_in_rect(POINT *, RECT *);

bool evaluate_swipe(TOUCH_HANDLE, SWIPE *);



#endif 

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
bool LT24_controller(uint32_t);

uint8_t display_digit(uint8_t );
void display_fps(uint32_t );

//	controllo valore dell'inerzia dei movimenti, proporzionale agli fps
inline float trasl_inertia(uint32_t fps){ return	((float)(0.8*60) / fps); }
inline float rot_inertia(uint32_t fps) { return	((float)(0.6*60) / fps); }

#endif 

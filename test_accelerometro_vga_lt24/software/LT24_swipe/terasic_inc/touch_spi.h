#ifndef TERASIC_TOUCHPANEL_H_
#define TERASIC_TOUCHPANEL_H_
#include "alt_types.h"
#include <stdint.h>
typedef void *TOUCH_HANDLE;

#define TRUE 1
#define FALSE 0


typedef struct{
    int     delta_x;
    int     delta_y;
    int     delta_t;
    int     previous_x;
    int     previous_y;
    int     current_x;
    int     current_y;
    int    point_valid;
    int    end_of_swipe;
}SWIPE;


TOUCH_HANDLE Touch_Init(const alt_u32 spi_base, const alt_u32 penirq_base, const alt_u32 penirq_irq);
void Touch_UnInit(TOUCH_HANDLE pHandle);
int Touch_GetXY(TOUCH_HANDLE p, int *x, int *y);
void Touch_EmptyFifo(TOUCH_HANDLE pHandle);
int evaluate_swipe(TOUCH_HANDLE, SWIPE *, uint32_t );


#endif /*TERASIC_TOUCHPANEL_H_*/

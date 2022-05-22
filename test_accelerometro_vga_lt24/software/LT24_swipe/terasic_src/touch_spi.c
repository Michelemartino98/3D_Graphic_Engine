#include "touch_spi.h"
#include <altera_avalon_spi.h>
#include "terasic_includes.h"
#include "alt_video_display.h"

//#define DEBUG_SWIPE

// debug config
//#define DEBUG_TOUCH_PANEL


#ifdef DEBUG_TOUCH_PANEL
    #define DEBUG_OUT(format, arg...) printf(format, ## arg);
#else
    #define DEBUG_OUT(format, arg...)
#endif

////////////// configuration //////////////
#define X_RES   SCREEN_WIDTH
#define Y_RES   SCREEN_HEIGHT
#define INVALID 0x0

// internal data structure
//#define ACTIVE_DELAY_TIME   (alt_ticks_per_second()/60)
#define ACTIVE_DELAY_TIME   (alt_ticks_per_second()/150)
#define SAMPLE_RATE         150  // times per seconds
#define FIFO_SIZE           2   // 10 modificato by us 

int touch_pending;


typedef struct{
    alt_u32 spi_base;
    alt_u32 penirq_base;
    alt_u32 penirq_irq;
    alt_u32 irq_mask;
    alt_u16 fifo_front;
    alt_u16 fifo_rear;
    alt_u16 fifo_x[FIFO_SIZE];
    alt_u16 fifo_y[FIFO_SIZE];

    bool pen_pressed;
    alt_alarm alarm;
    alt_u32 alarm_dur;
    // time measure
   // alt_u32 last_active_time;
    // disabled 
    alt_u32 next_active_time;
}TERASIC_TOUCH_PANEL;

// prototype of internal function
//static TOUCH_PANEL_CONTENT Touch;
#ifdef ALT_ENHANCED_INTERRUPT_API_PRESENT
void touch_isr(void* context);
#else
void touch_isr(void* context, alt_u32 id);
#endif
void touch_get_xy(TERASIC_TOUCH_PANEL *p);
void touch_clear_quque(TERASIC_TOUCH_PANEL *p);
void touch_xy_transform(int *x, int *y);
alt_u32 touch_alarm_callback(void *context);
void touch_enable_penirq(TERASIC_TOUCH_PANEL *p);
bool touch_is_pen_pressed(TERASIC_TOUCH_PANEL *p);
void touch_empty_fifo(TERASIC_TOUCH_PANEL *p);
void touch_clear_input(TERASIC_TOUCH_PANEL *p);

// init touch panel
TOUCH_HANDLE Touch_Init(const alt_u32 spi_base, const alt_u32 penirq_base, const alt_u32 penirq_irq){
    bool bSuccess = TRUE;
    
    TERASIC_TOUCH_PANEL *p;
    
    p = malloc(sizeof(TERASIC_TOUCH_PANEL));

    if (!p)
        return p;

    
    //
    memset(p, 0, sizeof(TERASIC_TOUCH_PANEL));
    p->spi_base = spi_base;
    p->penirq_base = penirq_base;
    p->irq_mask = 0x01;  // 1-pin
    p->penirq_irq = penirq_irq;
    p->alarm_dur = alt_ticks_per_second()/SAMPLE_RATE;
    
    // enalbe penirq_n interrupt (P1=1, P1=0)
    touch_enable_penirq(p);    
    

    // enable interrupt, 1-pin
    IOWR_ALTERA_AVALON_PIO_IRQ_MASK(p->penirq_base, p->irq_mask); 
    // Reset the edge capture register
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(p->penirq_base,0);
    // register ISR
    // register callback function

#ifdef ALT_ENHANCED_INTERRUPT_API_PRESENT
  if ((alt_ic_isr_register(TOUCH_PANEL_PEN_IRQ_N_IRQ_INTERRUPT_CONTROLLER_ID,
		                   p->penirq_irq,
		                   touch_isr,
		                   (void *)p,
		                   NULL
		                   ) != 0)){
 #else
  if ((alt_irq_register(p->penirq_irq, (void *)p, touch_isr) != 0)){
 #endif
        DEBUG_OUT(("[TOUCH]register IRQ fail\n"));
        bSuccess = FALSE;

    }else{        
        DEBUG_OUT(("[TOUCH]register IRQ success\n"));
    }

    if (bSuccess){    
        if (alt_alarm_start(&p->alarm, p->alarm_dur, touch_alarm_callback, p) == 0){
            DEBUG_OUT(("[TOUCH]alarm start success\n"));
        }else{
            DEBUG_OUT(("[TOUCH]alarm start fail\n"));
            bSuccess = FALSE;
        }
    }
    
    if (!bSuccess && p){
        free(p);
        p = NULL;

    }        
                
    return p;        
    

}

// uninit touch panel
void Touch_UnInit(TOUCH_HANDLE pHandle){
    TERASIC_TOUCH_PANEL *p = (TERASIC_TOUCH_PANEL *)pHandle;
    if (!p)
        return;
        
    // stop alarm
    alt_alarm_stop(&(p->alarm));
    // disable irq
    IOWR_ALTERA_AVALON_PIO_IRQ_MASK(p->penirq_base, 0x00);
    
    // zero varialbe
    free(p);
}


void Touch_EmptyFifo(TOUCH_HANDLE pHandle){
    TERASIC_TOUCH_PANEL *p = (TERASIC_TOUCH_PANEL *)pHandle;
    touch_empty_fifo(p);
}



// get x/y from internal FIFO
bool Touch_GetXY(TOUCH_HANDLE pHandle, int *x, int *y){
    TERASIC_TOUCH_PANEL *p = (TERASIC_TOUCH_PANEL *)pHandle;
    if (!p)
        return FALSE;    
    
    if (p->fifo_front == p->fifo_rear){
        // empty
        return FALSE;
    }
    *x = p->fifo_x[p->fifo_rear];
    *y = p->fifo_y[p->fifo_rear];
    //
    p->fifo_rear++;
    p->fifo_rear %= FIFO_SIZE;
    //
    // translate
    touch_xy_transform(x, y);
 
    //////////////////// 
    //modificato da noi, per girare l'orientamento dell'lt24 
        alt_u32 temp=*x; 
        *x=*y; 
        *y=240 - temp; 
    //////////////////// 
    
        DEBUG_OUT("[TOUCH] x=%d, y=%d\n", *x,*y); 
        printf("[TOUCH] x=%d, y=%d\n", *x,*y); 
    //    touch_clear_input(p); 
    //    touch_empty_fifo(p); 
        p->next_active_time = alt_nticks() + ACTIVE_DELAY_TIME; 

        return TRUE; 
    } 


// penirq_n ISR
#ifdef ALT_ENHANCED_INTERRUPT_API_PRESENT
void touch_isr(void* context){  
#else
void touch_isr(void* context, alt_u32 id){
#endif
    alt_u8 mask;
    TERASIC_TOUCH_PANEL *p = (TERASIC_TOUCH_PANEL *)context;

#ifdef ALT_ENHANCED_INTERRUPT_API_PRESENT
    alt_ic_irq_disable(TOUCH_PANEL_PEN_IRQ_N_IRQ_INTERRUPT_CONTROLLER_ID,TOUCH_PANEL_PEN_IRQ_N_IRQ);
#else
    alt_irq_disable(id);
#endif

    // get the edge capture mask
    mask = IORD_ALTERA_AVALON_PIO_EDGE_CAP(p->penirq_base);
    //if ((mask & Touch.irq_mask) == 0)  // 1-pin
    //    return;
    DEBUG_OUT("Touched!!\n");
    usleep(1000);
#if 0
    //Touch.pen_pressed = touch_is_pen_pressed();
    if (touch_is_pen_pressed()){
        Touch.last_active_time = alt_nticks();
        touch_get_xy();
    }else{ 
       // touch_empty_fifo();
    }
    IOWR(PIO_RED_LED_BASE, 0, Touch.pen_pressed);
#endif                    
    
    // Reset the edge capture register
    IOWR_ALTERA_AVALON_PIO_EDGE_CAP(p->penirq_base,0);    
    
//    touch_pending = TRUE;
//    printf("touch_pending nell' ISR = %d \n", touch_pending );

#ifdef ALT_ENHANCED_INTERRUPT_API_PRESENT
    alt_ic_irq_enable(TOUCH_PANEL_PEN_IRQ_N_IRQ_INTERRUPT_CONTROLLER_ID,TOUCH_PANEL_PEN_IRQ_N_IRQ);
#else
    //alt_irq_enable(id);   //++++++++++++++++++++++++++rischio di danno+++++++++++++++++++++++++++++++++++++++++++++++++++++
                            //va insieme a disabilitazione irq in ciclo for
#endif

}


void touch_empty_fifo(TERASIC_TOUCH_PANEL *p){
    p->fifo_rear = p->fifo_front;
}

bool touch_is_pen_pressed(TERASIC_TOUCH_PANEL *p){
    bool bPressed;
    bPressed = (IORD(p->penirq_base, 0) & 0x01)?FALSE:TRUE;
    return bPressed;
}


void touch_enable_penirq(TERASIC_TOUCH_PANEL *p){
    const alt_u8 CommandGetX = 0x82;
    const alt_u8 CommandGetY = 0xD2;
    alt_u8 data8;
    
    alt_avalon_spi_command(p->spi_base, 0, sizeof(CommandGetX), &CommandGetX, 0, 0, ALT_AVALON_SPI_COMMAND_MERGE);
    alt_avalon_spi_command(p->spi_base, 0, 0, 0, sizeof(data8), (alt_u8*)&data8, ALT_AVALON_SPI_COMMAND_MERGE);
    alt_avalon_spi_command(p->spi_base, 0, 0, 0, sizeof(data8), (alt_u8*)&data8, ALT_AVALON_SPI_COMMAND_TOGGLE_SS_N);
   
    alt_avalon_spi_command(p->spi_base, 0, sizeof(CommandGetY), &CommandGetY, 0, 0, ALT_AVALON_SPI_COMMAND_MERGE);
    alt_avalon_spi_command(p->spi_base, 0, 0, 0, sizeof(data8), (alt_u8*)&data8, ALT_AVALON_SPI_COMMAND_MERGE);
    alt_avalon_spi_command(p->spi_base, 0, 0, 0, sizeof(data8), (alt_u8*)&data8, ALT_AVALON_SPI_COMMAND_TOGGLE_SS_N);
}

void touch_clear_input(TERASIC_TOUCH_PANEL *p){
    touch_enable_penirq(p);
}


// get x/y by SPI command
void touch_get_xy(TERASIC_TOUCH_PANEL *p){
    alt_u16 x, y;
    int result;
    const alt_u8 CommandGetX = 0x92;
    const alt_u8 CommandGetY = 0xD2;
    alt_u16 ResponseX, ResponseY;
    alt_u8 high_byte, low_byte;
    
       
    //DEBUG_OUT(("[TOUCH] get x/y\n"));

    // x
    result = alt_avalon_spi_command(p->spi_base, 0, sizeof(CommandGetX), &CommandGetX, 0, 0, ALT_AVALON_SPI_COMMAND_MERGE);
    result = alt_avalon_spi_command(p->spi_base, 0, 0, 0, sizeof(high_byte), (alt_u8*)&high_byte, ALT_AVALON_SPI_COMMAND_MERGE);
    if (result != sizeof(high_byte)){
        DEBUG_OUT(("[TOUCH] failed to get x\n"));
        return;
    }          
    result = alt_avalon_spi_command(p->spi_base, 0, 0, 0, sizeof(low_byte), (alt_u8*)&low_byte, ALT_AVALON_SPI_COMMAND_TOGGLE_SS_N);
    if (result != sizeof(low_byte)){
        DEBUG_OUT(("[TOUCH] failed to get x\n"));
        return;
    }  
    ResponseX = (high_byte << 8) | low_byte;        
    
    // y
    result = alt_avalon_spi_command(p->spi_base, 0, sizeof(CommandGetY), &CommandGetY, 0, 0, ALT_AVALON_SPI_COMMAND_MERGE);
    result = alt_avalon_spi_command(p->spi_base, 0, 0, 0, sizeof(high_byte), (alt_u8*)&high_byte, ALT_AVALON_SPI_COMMAND_MERGE);
    if (result != sizeof(high_byte)){
        DEBUG_OUT(("[TOUCH] failed to get x\n"));
        return;
    }          
    result = alt_avalon_spi_command(p->spi_base, 0, 0, 0, sizeof(low_byte), (alt_u8*)&low_byte, ALT_AVALON_SPI_COMMAND_TOGGLE_SS_N);
    if (result != sizeof(low_byte)){
        DEBUG_OUT(("[TOUCH] failed to get x\n"));
        return;
    }  
    ResponseY = (high_byte << 8) | low_byte;        

    if (!touch_is_pen_pressed(p))
        return; // do not use this data    
        
    x = (ResponseX >> 3 ) & 0xFFF;  // 12 bits    
    y = (ResponseY >> 3 ) & 0xFFF;  // 12 bits
    
    
    // check whether the fifo is full!
    if (((p->fifo_front+1)%FIFO_SIZE) == p->fifo_rear){
        // full, pop an old one
        p->fifo_rear++;
        p->fifo_rear %= FIFO_SIZE;        
        
    }
    DEBUG_OUT("[ ADC] x=%d, y=%d\n", x,y);


    //modificato da noi, per girare l'orientamento dell'lt24 

    alt_u32 x_aux = y; 
    alt_u32 y_aux =240 - x; 

    printf("[ ADC] x=%d, y=%d\n", x_aux,y_aux);
    // push now    
    
  //  p->fifo_x[p->fifo_front] = x; 
  //  p->fifo_y[p->fifo_front] = y;     
  //  p->fifo_front++; 
  //  p->fifo_front %= FIFO_SIZE;    

 
//hack immondo  
    p->fifo_x[0] = x; 
    p->fifo_x[1] = x; 
    p->fifo_y[0] = y; 
    p->fifo_y[1] = y;    
    p->fifo_front++; 
    p->fifo_front %= FIFO_SIZE;      
}





// polling x/y when penirq_n is low
alt_u32 touch_alarm_callback(void *context){
    TERASIC_TOUCH_PANEL *p = (TERASIC_TOUCH_PANEL *)context;
    
    if (touch_is_pen_pressed(p)){//Touch.pen_pressed){
        if (alt_nticks() > p->next_active_time)
            touch_get_xy(p);
            touch_pending = TRUE;
      //  p->last_active_time = alt_nticks(); 
    }else{
       // touch_empty_fifo(p);
        //if ((alt_nticks() - Touch.last_active_time) > alt_ticks_per_second()/10){
         touch_enable_penirq(p);                                                                //cosa diavolo ci fanno?
         touch_clear_input(p);                                                                  //sembra funzionare senza, ma dopo un po' si blocca
          //  p->last_active_time = alt_nticks(); 
        //}            
    }        
    return p->alarm_dur;
}

void touch_xy_transform(int *x, int *y){
    int xx, yy;
    const int y_ignore = 200;
    xx = *y;
    yy = *x;

    // scale & swap
   // xx = 4096 -1 - xx;
    xx = xx * X_RES / 4096;

   // yy = 4096 -1 - yy;

    // special calibrate for LT24
    if (yy > (4096-y_ignore))
    	yy = 4096-y_ignore;
    yy = yy * 4095/ (4096-y_ignore);
    
    yy = yy * Y_RES / 4096;

    // swap
    *x = xx;
    *y = yy;    
    
}


int evaluate_swipe(TOUCH_HANDLE pHandle, SWIPE *touch_swipe, POINT *pt, uint32_t delta_t){

	TERASIC_TOUCH_PANEL *tpanel = (TERASIC_TOUCH_PANEL *)pHandle;
	if(touch_pending){ 							//prima della chiamata di questa funzione � stato registrato un tocco,
												//	quindi inizio a discriminare tra tocco e swipe

		touch_swipe->delta_t = alt_timestamp();	// Acquisisco il tempo

		int x,y;

		if(touch_swipe->point_valid){ 			//tocco predendente era valido, quindi calcolo i parametri dello swipe
 												//sarebbe da passargli direttamente il campo della struttura
			touch_swipe->previous_x = touch_swipe->current_x;
			touch_swipe->previous_y = touch_swipe->current_y;
			touch_swipe->current_x = pt->x;
			touch_swipe->current_y = pt->y;
			touch_swipe->delta_x = touch_swipe->current_x - touch_swipe->previous_x;
			touch_swipe->delta_y = touch_swipe->current_y - touch_swipe->previous_y;
            printf("point valid precedente valido\n");
            
		}


		else {									//tocco precedente non esisteva, quindi mi limito a salvare i valori correnti
			touch_swipe->previous_x = INVALID;	//INVALID magari utili per debug, ma si possono levare tranquillamente poi
			touch_swipe->previous_y = INVALID;
			touch_swipe->current_x = pt->x;
			touch_swipe->current_y = pt->y;
			touch_swipe->delta_x = INVALID;
			touch_swipe->delta_y = INVALID;
			touch_swipe->end_of_swipe = FALSE;	//ho nuovo tocco, quindi fermo end_of_swipe
			touch_swipe->point_valid = TRUE;
            printf("point valid precedente NON valido\n");
		}
		touch_pending = FALSE;				    //resetto il flag che verr� rimesso alto dalla isr del touch
	}
	else{										//isr non ha registrato tocco
		if(touch_swipe->point_valid){			//	ma se ultimo controllo era valido, significa che � la fine di uno swipe
			touch_swipe->end_of_swipe = TRUE;
		}
		touch_swipe->point_valid = FALSE;		//quindi prossimo tocco sicuramente non risulter� in uno swipe
		printf("NO TOUCH PENDING\n");
	}

    printf("delta_x = %d\t\t", touch_swipe->delta_x);
	printf("delta_y = %d\n", touch_swipe->delta_y);
	#if defined(DEBUG_SWIPE)
		printf("current_x = %d\t\t", touch_swipe->current_x);
		printf("current_y = %d\n", touch_swipe->current_y);
		printf("previous_x = %d\t\t", touch_swipe->previous_x);
		printf("previous_y = %d\n", touch_swipe->previous_y);
		printf("delta_t = %d\t\t", touch_swipe->delta_t);
		printf("delta_x = %d\t\t", touch_swipe->delta_x);
		printf("delta_y = %d\n", touch_swipe->delta_y);
		printf("point_valid = %d\n", touch_swipe->point_valid);

		printf("\n");
	#endif /*DEBUG_SWIPE*/
}

//file contenente file per controllo comandi tramite accelerometro
#include "../inc/config.h"

alt_up_accelerometer_spi_dev * accelerometer_dev;

extern Graphic_engine Object_3D;

void init_accelerometer(){
    accelerometer_dev = alt_up_accelerometer_spi_open_dev ("/dev/accelerometer_spi");
    //#ifdef DEBUG_ACC
    if ( accelerometer_dev == NULL)
        printf ("Error: could not open acc device \n");
    else
        printf ("Opened accelerometer device \n");
//#endif
}



void accelerometer_controller(){
    
    //parametri per uso dell'accelerometro+slider
    static int32_t x_acc = 0;
    static int32_t y_acc = 0;


    uint16_t slider_data_reg;
    uint16_t edge_capture_k1;
    static bool     command_sw=true; 

    static float inc_tx=0;
    static float inc_ty=0;

    static float inc_rx=0;
    static float inc_ry=0;


    slider_data_reg = IORD_ALTERA_AVALON_PIO_DATA(SLIDERS_BASE);
    alt_up_accelerometer_spi_read_x_axis(accelerometer_dev, &x_acc);
    alt_up_accelerometer_spi_read_y_axis(accelerometer_dev, &y_acc);
    
    //ROTAZIONE
    if(slider_data_reg & BIT(9)){
        if( ABS(x_acc) > ACC_TH || ABS(y_acc) > ACC_TH){    // ACC_TH è una soglia per filtrare un po' l'accelerometro e evitare che anche in piano il cubo si muova
            inc_rx= (float)y_acc / G_ACC * MAX_INC_R;
            Object_3D.update_rotation_relative( inc_rx, X);
            inc_ry= (float)x_acc / G_ACC * MAX_INC_R;
            Object_3D.update_rotation_relative( inc_ry, Z);
        }
    }
    //TRASLAZIONE
    else{
        if( ABS(x_acc) > ACC_TH || ABS(y_acc) > ACC_TH){
            inc_tx= (float)-x_acc / G_ACC * MAX_INC_T;
            Object_3D.update_translation_relative(inc_tx , X);
            inc_ty= (float)y_acc / G_ACC * MAX_INC_T;
            Object_3D.update_translation_relative(inc_ty , Y);
        } 
    }
    //SCALA
    if(slider_data_reg & BIT(4)){                       //il segno dell'incremento della scala sta su slider9    
        if(slider_data_reg & (BIT(0) | BIT(3))){                   //scala x
            Object_3D.update_scaling_relative( INC_S , X );
        }
        if(slider_data_reg & (BIT(1) | BIT(3))){                   //scala y
            Object_3D.update_scaling_relative( INC_S , Y );
        }
        if(slider_data_reg & (BIT(2) | BIT(3))){                   //scala z
            Object_3D.update_scaling_relative( INC_S , Z );
        }
    }
    else {                                              //incremento negativo
        if(slider_data_reg & (BIT(0) | BIT(3))){ 
            Object_3D.update_scaling_relative( -INC_S , X );
        }
        if(slider_data_reg & (BIT(1) | BIT(3))){ 
            Object_3D.update_scaling_relative( -INC_S , Y );
        }
        if(slider_data_reg & (BIT(2) | BIT(3))){ 
            Object_3D.update_scaling_relative( -INC_S , Z );
        }
    }
    #ifdef DEBUG_ACC
    printf("%f %f \n", inc_rx, inc_rz );
    #endif

}

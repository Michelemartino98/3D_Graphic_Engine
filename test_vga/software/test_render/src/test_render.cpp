
#include "../inc/config.h"


alt_up_pixel_buffer_dma_dev *pixel_buf_dma_dev;

int main(){
    
    pixel_buf_dma_dev = alt_up_pixel_buffer_dma_open_dev("/dev/video_pixel_buffer_dma_0");

    Cube_3D Cube;

    //variabili per uso degli slider
    float sx = 0.5;
    float sy = 0.5;
    float sz = 0.5;
    
    float x = 0;
    float y = 0;
    float z = 3;

    float rx = 0;
    float ry = 0;
    float rz = 0;

    uint16_t slider_data_reg;
    uint16_t inc_pos; //segno dell'incremento

    float inc_s = 0.005;
    float inc_t = 0.005;
    float inc_r = M_PI/800;
    
 
    int current_frame = 0;
 
    for(;;){

        
        slider_data_reg = IORD_ALTERA_AVALON_PIO_DATA(SLIDERS_BASE);


        if(slider_data_reg & BIT(9)){                        //se 1 incremento positivo

            if(slider_data_reg & BIT(0)){ //scala x
                sx+=inc_s;
            }
            if(slider_data_reg & BIT(1)){ //scala y
                sy+=inc_s;
            }
            if(slider_data_reg & BIT(2)){ //scala y
                sz+=inc_s;
            }
            if(slider_data_reg & BIT(3)){ //trasla x
                x+=inc_t;
            }
            if(slider_data_reg & BIT(4)){ //trasla y
                y+=inc_t;
            }
            if(slider_data_reg & BIT(5)){ //trasla z
                z+=inc_t;
            }
            if(slider_data_reg & BIT(6)){ //ruota x
                rx+=inc_r;
            }
            if(slider_data_reg & BIT(7)){ //ruota y
                ry+=inc_r;
            }
            if(slider_data_reg & BIT(8)){ //ruota z
                rz+=inc_r;
            }
        }

        else {                              //incremento negativo
            if(slider_data_reg & BIT(0)){ //scala x
                sx-=inc_s;
            }
            if(slider_data_reg & BIT(1)){ //scala y
                sy-=inc_s;
            }
            if(slider_data_reg & BIT(2)){ //scala y
                sz-=inc_s;
            }
            if(slider_data_reg & BIT(3)){ //trasla x
                x-=inc_t;
            }
            if(slider_data_reg & BIT(4)){ //trasla y
                y-=inc_t;
            }
            if(slider_data_reg & BIT(5)){ //trasla z
                z-=inc_t;
            }
            if(slider_data_reg & BIT(6)){ //ruota x
                rx-=inc_r;
            }
            if(slider_data_reg & BIT(7)){ //ruota y
                ry-=inc_r;
            }
            if(slider_data_reg & BIT(8)){ //ruota z
                rz-=inc_r;
            }
        }
        Cube.update_scaling( sx , sy , sz);
        Cube.update_translation( x , y , z);
        Cube.update_rotation( rx , ry , rz );

        #ifdef DEBUG_1
    	printf("FRAME %d\n", current_frame++);
        #endif /*DEBUG_1*/
            
        Cube.calculate_rendering();
        Cube.display_frame(); 

    }
}

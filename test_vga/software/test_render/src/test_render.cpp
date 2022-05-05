
#include "../inc/config.h"


alt_up_pixel_buffer_dma_dev *pixel_buf_dma_dev;

int main(){
    
    pixel_buf_dma_dev = alt_up_pixel_buffer_dma_open_dev("/dev/video_pixel_buffer_dma_0");

    Cube_3D Cube;
    
    //per test movimento
    int k = 0;
 
    int current_frame = 0;
    float z_inc = 0;        
    float zzz=0;
    for(;;){

        #ifdef DEBUG_1
    	printf("FRAME %d\n", current_frame++);
        #endif /*DEBUG_1*/

        zzz+=0.0005;
        Cube.update_translation(zzz,0,3);

            // if (k<800){
        	// 		z_inc+= M_PI/400 ;
            //         Cube.update_rotation(z_inc,0,0);
        	// 		k++;
        	// }
            // else if (k<1600){
        	// 		z_inc+= M_PI/400 ;
            //         Cube.update_rotation(0,z_inc,0);

        	// 		k++;
        	// }
            // else if (k<2400){
        	// 		z_inc+= M_PI/400 ;
            //         Cube.update_rotation(0,0,z_inc);
        	// 		k++;
        	// }
            
            Cube.calculate_rendering();
            Cube.display_frame(); 

    }
}

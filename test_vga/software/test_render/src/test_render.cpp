
#include "../inc/config.h"


alt_up_pixel_buffer_dma_dev *pixel_buf_dma_dev;



int main(){
    
    pixel_buf_dma_dev = alt_up_pixel_buffer_dma_open_dev("/dev/video_pixel_buffer_dma_0");

    Cube_3D Cube;

    
    //per test movimento
    int k = 0;
 
    int current_frame = 0;
    float z_inc = 0;        

    for(;;){

        #ifdef DEBUG_1
    	printf("FRAME %d\n", current_frame++);
        #endif /*DEBUG_1*/



            if (k<800){
        			z_inc+= M_PI/400 ;
                    Cube.update_rotation(z_inc,0,0);
                    Cube.update_scaling(0.3,0.5,0.5);
        			k++;
        	}
            else if (k<1600){
        			z_inc+= M_PI/400 ;
                    Cube.update_rotation(0,z_inc,0);
                    Cube.update_scaling(0.5,0.2,0.5);
        			k++;
        	}
            else if (k<2400){
        			z_inc+= M_PI/400 ;
                    Cube.update_rotation(0,0,z_inc);
                    Cube.update_scaling(0.5,0.2,0.7);
        			k++;
        	}
            
        	//test spostamento grezzo
        	// if (k<2000){
        	// 	for(int i=0; i<8; i++){
        	// 		Cube.vertex[M8(Z,i)]-=0.08;
        	// 		k++;
        	// 		printf("z(%d) = %f\n", i, Cube.vertex[M8(Z,i)]);
        	// 	}
        	// }
            Cube.Matrix4x4MultiplyBy4x4(Cube.projection_matrix, Cube.translation_matrix, Cube.proj_trasl);
            Cube.Matrix4x4MultiplyBy4x4(Cube.proj_trasl, Cube.rotation_matrix, Cube.proj_trasl_rot);
            Cube.Matrix4x4MultiplyBy4x4(Cube.proj_trasl_rot, Cube.scaling_matrix, Cube.complete_matrix);
            
            // for (int i = 0; i < 4*4; i++)
            // {
            //     printf("M(%d) = %f\n", i, Cube.projection_matrix[i]);
            // }
            Cube.vector_matrix_multiply();
            Cube.from_3D_to_2D();
            Cube.display_frame(); 

    }
}

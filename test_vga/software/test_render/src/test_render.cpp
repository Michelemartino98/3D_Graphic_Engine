
#include "../inc/config.h"


alt_up_pixel_buffer_dma_dev *pixel_buf_dma_dev;



int main(){
    
    pixel_buf_dma_dev = alt_up_pixel_buffer_dma_open_dev("/dev/video_pixel_buffer_dma_0");

    Cube_3D Cube;

    
    //per test movimento
    int k = 0;
 
    int current_frame = 0;
    float z_inc = 0;
    	
        		for(int i=0; i<8; i++){
        			Cube.vertex[M8(Z,i)]-=2.5;
        			k++;
        			printf("z(%d) = %f\n", i, Cube.vertex[M8(Z,i)]);
        		}
        

    for(;;){

        #ifdef DEBUG_1
    	printf("FRAME %d\n", current_frame++);
        #endif /*DEBUG_1*/

		//Cube.Matrix4x4MultiplyBy4x4(Cube.scaling_matrix, Cube.rotation_matrix, Cube.scal_rot);
		//Cube.Matrix4x4MultiplyBy4x4(Cube.scal_rot, Cube.translation_matrix, Cube.scal_rot_trasl);
		//Cube.Matrix4x4MultiplyBy4x4(Cube.scal_rot_trasl, Cube.projection_matrix, Cube.complete_matrix);

            /*if (k<2000){
        			z_inc+=0.08;
                    Cube.update_translation(0,0,z_inc);
        			k++;    		
        	}
			*/
            
        	//test spostamento grezzo
        	// if (k<2000){
        	// 	for(int i=0; i<8; i++){
        	// 		Cube.vertex[M8(Z,i)]-=0.08;
        	// 		k++;
        	// 		printf("z(%d) = %f\n", i, Cube.vertex[M8(Z,i)]);
        	// 	}
        	// }

            Cube.Matrix4x4MultiplyBy4x4(Cube.identity_matrix, Cube.projection_matrix, Cube.complete_matrix);

            // for (int i = 0; i < 4*4; i++)
            // {
            //     printf("M(%d) = %f\n", i, Cube.projection_matrix[i]);
            // }
            Cube.vector_matrix_multiply();
            Cube.from_3D_to_2D();
            Cube.display_frame(); 

    }
}

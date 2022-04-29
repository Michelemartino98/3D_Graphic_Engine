
#include "../inc/config.h"


alt_up_pixel_buffer_dma_dev *pixel_buf_dma_dev;

int k = 0;

int main(){
    

    pixel_buf_dma_dev = alt_up_pixel_buffer_dma_open_dev("/dev/video_pixel_buffer_dma_0");

    Cube_3D Cube;


    for(;;){

		
		//complete = rotation X scaling
//		Cube.Matrix4x4MultiplyBy4x4(Cube.rotation_matrix, Cube.scaling_matrix, Cube.complete_matrix);
		//complete = translation X complete = translation X rotation X scaling
//		Cube.Matrix4x4MultiplyBy4x4(Cube.translation_matrix, Cube.complete_matrix, Cube.complete_matrix);
		//complete = projection X translation X rotation X scaling
//		Cube.Matrix4x4MultiplyBy4x4(Cube.projection_matrix, Cube.complete_matrix, Cube.complete_matrix);

    	//debug di disperazione
    	//Cube.Matrix4x4MultiplyBy4x4(Cube.scaling_matrix, Cube.projection_matrix, Cube.complete_matrix);

        Cube.vector_matrix_multiply();
        Cube.from_3D_to_2D();
        Cube.display_frame(); 
    }
}

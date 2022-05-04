
#include "../inc/config.h"


alt_up_pixel_buffer_dma_dev *pixel_buf_dma_dev;

int k = 0;

int main(){
    

    pixel_buf_dma_dev = alt_up_pixel_buffer_dma_open_dev("/dev/video_pixel_buffer_dma_0");

    Cube_3D Cube;

    
    for(;;){



		//Cube.Matrix4x4MultiplyBy4x4(Cube.scaling_matrix, Cube.rotation_matrix, Cube.scal_rot);
	//
		//Cube.Matrix4x4MultiplyBy4x4(Cube.scal_rot, Cube.translation_matrix, Cube.scal_rot_trasl);
//
		//Cube.Matrix4x4MultiplyBy4x4(Cube.scal_rot_trasl, Cube.projection_matrix, Cube.complete_matrix);


        Cube.vector_matrix_multiply();
        Cube.from_3D_to_2D();
        Cube.display_frame(); 
    }
}

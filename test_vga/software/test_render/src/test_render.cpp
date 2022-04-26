
#include "../inc/config.h"

alt_up_pixel_buffer_dma_dev *pixel_buf_dma_dev;

int main(){
    
    pixel_buf_dma_dev = alt_up_pixel_buffer_dma_open_dev("/dev/video_pixel_buffer_dma_0");

    Cube_3D Cube;

        Cube.vector_matrix_multiply();
        Cube.display_frame(); 
        Cube.from_3D_to_2D();
    for(;;){
    }
}

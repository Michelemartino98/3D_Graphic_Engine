
#include "../inc/config.h"


alt_up_pixel_buffer_dma_dev *pixel_buf_dma_dev;

int k = 0;

int main(){
    

    pixel_buf_dma_dev = alt_up_pixel_buffer_dma_open_dev("/dev/video_pixel_buffer_dma_0");

    Cube_3D Cube;


    for(;;){
    	k++;
    	printf("frame %d\n", k);
    	if(k<40){
    	for(int i=0; i<8; i++){
    		Cube.vertex[i][Z]-=0.08;
    	}
    	}
    	else if(k<80)
    	{
        	for(int i=0; i<8; i++){
        		Cube.vertex[i][Y]-=0.02;
        	}
    	}
    	else {
    		for(int i = 0; i<8; i++){
    			Cube.vertex[i][X]+=0.02;
    		}
    	}

        Cube.vector_matrix_multiply();
        Cube.from_3D_to_2D();
        Cube.display_frame(); 
    }
}

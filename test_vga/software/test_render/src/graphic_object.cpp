#include "../inc/config.h"

extern alt_up_pixel_buffer_dma_dev *pixel_buf_dma_dev;

Cube_3D::Cube_3D(){

    update_position(0, 0, 0);
    update_rotation(0, 0, 0);
    update_scaling(1, 1, 1);

    
    r = imageAspectRatio * scale;
    l = -r;
    t = scale;
    b = -t;

    // set OpenGL perspective projection matrix
    projection_matrix[0][0] = 2 * n / (r - l); 
    projection_matrix[0][1] = 0; 
    projection_matrix[0][2] = 0; 
    projection_matrix[0][3] = 0; 
 
    projection_matrix[1][0] = 0; 
    projection_matrix[1][1] = 2 * n / (t - b); 
    projection_matrix[1][2] = 0; 
    projection_matrix[1][3] = 0; 
 
    projection_matrix[2][0] = 0; 
    projection_matrix[2][1] = 0; 
    projection_matrix[2][2] = -(f + n) / (f - n); 
    projection_matrix[2][3] = -1; 
 
    projection_matrix[3][0] = 0; 
    projection_matrix[3][1] = 0; 
    projection_matrix[3][2] = -2 * f * n / (f - n); 
    projection_matrix[3][3] = 0; 
}

void Cube_3D::update_position(float x, float y,float z){
    position[X] = x;
    position[Y] = y;
    position[Z] = z;
}

void Cube_3D::update_rotation(float rx, float ry, float rz){
    rotation[X] = rx;
    rotation[Y] = ry;
    rotation[Z] = rz;
}

void Cube_3D::update_scaling(float sx, float sy, float sz){
    scaling[X] = sx;
    scaling[Y] = sy;
    scaling[Z] = sz;
}

int Cube_3D::display_frame(){
    //pulisco il back buffer
    alt_up_pixel_buffer_dma_clear_screen_delayed(pixel_buf_dma_dev,1);

    //disegno i pixel
    for(int i=0; i<N_VERTEX; i++){
        alt_up_pixel_buffer_dma_draw(pixel_buf_dma_dev, WHITE, vertex_on_2D[i][X], vertex_on_2D[i][Y]);
    }

    //swap del buffer, e attesa che sia eseguito
    alt_up_pixel_buffer_dma_swap_buffers(pixel_buf_dma_dev);
    while (alt_up_pixel_buffer_dma_check_swap_buffers_status(pixel_buf_dma_dev)){;}
    return 0;
}

void Cube_3D::vector_matrix_multiply(){
	printf("START PRINT Z\n");
    for(int i = 0; i < N_VERTEX; i++){
        transformed_vertex[i][X] =  vertex[i][X]*projection_matrix[0][0] + \
                                    vertex[i][Y]*projection_matrix[1][0] + \
                                    vertex[i][Z]*projection_matrix[2][0] + \
                                    vertex[i][W]*projection_matrix[3][0];
                    
        transformed_vertex[i][Y] =  vertex[i][X]*projection_matrix[0][1] + \
                                    vertex[i][Y]*projection_matrix[1][1] + \
                                    vertex[i][Z]*projection_matrix[2][1] + \
                                    vertex[i][W]*projection_matrix[3][1];

        transformed_vertex[i][Z] =  vertex[i][X]*projection_matrix[0][2] + \
                                    vertex[i][Y]*projection_matrix[1][2] + \
                                    vertex[i][Z]*projection_matrix[2][2] + \
                                    vertex[i][W]*projection_matrix[3][2];
                            
        transformed_vertex[i][W] =  vertex[i][X]*projection_matrix[0][3] + \
                                    vertex[i][Y]*projection_matrix[1][3] + \
                                    vertex[i][Z]*projection_matrix[2][3] + \
                                    vertex[i][W]*projection_matrix[3][3];             

        /* Per debug, controllare se tutti i punti calcolati abbiano la stessa z*/

        printf("p%d : z%f\n", i, transformed_vertex[i][Z]);

                             
    }
    printf("END PRINT Z\n");
}

void Cube_3D::from_3D_to_2D(){
    for(int i = 0; i < N_VERTEX; i++){
        vertex_on_2D[i][X] = (transformed_vertex[i][X]/(X_RES*2))+(X_RES/2);
        vertex_on_2D[i][Y] = (transformed_vertex[i][Y]/(Y_RES*2))+(Y_RES/2);

    }
}
 
int Cube_3D::calculate_world(){
    
}

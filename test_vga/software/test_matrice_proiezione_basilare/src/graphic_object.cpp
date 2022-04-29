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
    //for(int i=0; i<N_VERTEX; i++){
    //    alt_up_pixel_buffer_dma_draw(pixel_buf_dma_dev, WHITE, vertex_on_2D[i][X], vertex_on_2D[i][Y]);
    //}
    //disegno i lati del cubo
    alt_up_pixel_buffer_dma_draw_line(pixel_buf_dma_dev,vertex_on_2D[0][X],vertex_on_2D[0][Y],vertex_on_2D[1][X],vertex_on_2D[1][Y], GREEN, 1);
    alt_up_pixel_buffer_dma_draw_line(pixel_buf_dma_dev,vertex_on_2D[0][X],vertex_on_2D[0][Y],vertex_on_2D[2][X],vertex_on_2D[2][Y], GREEN, 1);
    alt_up_pixel_buffer_dma_draw_line(pixel_buf_dma_dev,vertex_on_2D[0][X],vertex_on_2D[0][Y],vertex_on_2D[4][X],vertex_on_2D[4][Y], GREEN, 1);
    alt_up_pixel_buffer_dma_draw_line(pixel_buf_dma_dev,vertex_on_2D[1][X],vertex_on_2D[1][Y],vertex_on_2D[6][X],vertex_on_2D[6][Y], GREEN, 1);
    alt_up_pixel_buffer_dma_draw_line(pixel_buf_dma_dev,vertex_on_2D[1][X],vertex_on_2D[1][Y],vertex_on_2D[5][X],vertex_on_2D[5][Y], GREEN, 1);
    alt_up_pixel_buffer_dma_draw_line(pixel_buf_dma_dev,vertex_on_2D[2][X],vertex_on_2D[2][Y],vertex_on_2D[3][X],vertex_on_2D[3][Y], GREEN, 1);
    alt_up_pixel_buffer_dma_draw_line(pixel_buf_dma_dev,vertex_on_2D[2][X],vertex_on_2D[2][Y],vertex_on_2D[6][X],vertex_on_2D[6][Y], GREEN, 1);
    alt_up_pixel_buffer_dma_draw_line(pixel_buf_dma_dev,vertex_on_2D[3][X],vertex_on_2D[3][Y],vertex_on_2D[4][X],vertex_on_2D[4][Y], GREEN, 1);
    alt_up_pixel_buffer_dma_draw_line(pixel_buf_dma_dev,vertex_on_2D[3][X],vertex_on_2D[3][Y],vertex_on_2D[7][X],vertex_on_2D[7][Y], GREEN, 1);
    alt_up_pixel_buffer_dma_draw_line(pixel_buf_dma_dev,vertex_on_2D[4][X],vertex_on_2D[4][Y],vertex_on_2D[5][X],vertex_on_2D[5][Y], GREEN, 1);
    alt_up_pixel_buffer_dma_draw_line(pixel_buf_dma_dev,vertex_on_2D[5][X],vertex_on_2D[5][Y],vertex_on_2D[7][X],vertex_on_2D[7][Y], GREEN, 1);
    alt_up_pixel_buffer_dma_draw_line(pixel_buf_dma_dev,vertex_on_2D[6][X],vertex_on_2D[6][Y],vertex_on_2D[7][X],vertex_on_2D[7][Y], GREEN, 1);

    //swap del buffer, e attesa che sia eseguito
    alt_up_pixel_buffer_dma_swap_buffers(pixel_buf_dma_dev);
    while (alt_up_pixel_buffer_dma_check_swap_buffers_status(pixel_buf_dma_dev)){;}
    return 0;
}

void Cube_3D::vector_matrix_multiply(){
	printf("START PRINT 3D COORDINATES\n");
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

        printf("PRIMA DI DIVISIONE\n");
        printf("p%d : x%f\n", i, transformed_vertex[i][X]);
        printf("p%d : y%f\n", i, transformed_vertex[i][Y]);
        printf("p%d : z%f\n", i, transformed_vertex[i][Z]);
        printf("p%d : w%f\n", i, transformed_vertex[i][W]);


        for (int c = 0; c < 8; c++)
        {
        	transformed_vertex[c][X]/=transformed_vertex[c][W];
        	transformed_vertex[c][Y]/=transformed_vertex[c][W];
        	transformed_vertex[c][Z]/=transformed_vertex[c][W];
        	transformed_vertex[c][W]=1;

        }
        printf("DOPO DIVISIONE\n");

        printf("p%d : x%f\n", i, transformed_vertex[i][X]);
        printf("p%d : y%f\n", i, transformed_vertex[i][Y]);
        printf("p%d : z%f\n", i, transformed_vertex[i][Z]);
        printf("p%d : w%f\n", i, transformed_vertex[i][W]);


                             
    }
    printf("END PRINT 3D COORDINATES\n");
}

void Cube_3D::from_3D_to_2D(){
	printf("START PRINT 2D COORDINATES\n");
    for(int i = 0; i < N_VERTEX; i++){
    	if((transformed_vertex[i][X]>1) | (transformed_vertex[i][X]<-1)){
    		vertex_on_2D[i][X] = 0;
    	}
    	else{
    		vertex_on_2D[i][X] = ((transformed_vertex[i][X]*(X_RES/2))+(X_RES/2));
    	}
    	if((transformed_vertex[i][Y]>1) | (transformed_vertex[i][Y]<-1)){
    		vertex_on_2D[i][Y] = 0;
    	}
    	else{
            vertex_on_2D[i][Y] = ((transformed_vertex[i][Y]*(Y_RES/2))+(Y_RES/2));
    	}



        printf("p%d : x%f\n", i, transformed_vertex[i][X]);
        printf("p%d : y%f\n", i, transformed_vertex[i][Y]);
        printf("p%d : z%f\n", i, transformed_vertex[i][Z]);
        printf("p%d : w%f\n", i, transformed_vertex[i][W]);

        printf("p%d - x:%d / y:%d\n",i, vertex_on_2D[i][X], vertex_on_2D[i][Y]);
    }
    printf("END PRINT 2D COORDINATES\n");
}
 
int Cube_3D::calculate_world(){
    return 1;
}

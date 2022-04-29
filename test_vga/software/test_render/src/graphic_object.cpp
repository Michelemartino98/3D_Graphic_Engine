#include "../inc/config.h"

extern alt_up_pixel_buffer_dma_dev *pixel_buf_dma_dev;

Cube_3D::Cube_3D(){

    update_translation(0, 0, -15);
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

    //parametri per calcolo matrice di rotazione
    /*
                        |  CE      -CF       D   0|
    rotation_matrix  =  |  BDE+AF  -BDF+AE  -BC  0|
                        | -ADE+BF   ADF+BE   AC  0|
                        |  0        0        0   1|

    A       = cos(angle_x));
    B       = sin(angle_x);
    C       = cos(angle_y);
    D       = sin(angle_y);
    E       = cos(angle_z);
    F       = sin(angle_z);
     
    nel nostro codice si ha::
    rotation[X]=angle_x;
    rotation[Y]=angle_y;
    rotation[Z]=angle_z;
    */

//    rotation_matrix[0][0] = cos(rotation[Y])*cos(rotation[Z]); 
//    rotation_matrix[0][1] = -cos(rotation[Y])*sin(rotation[Z]);
//    rotation_matrix[0][2] = sin(rotation[Y]);
//    rotation_matrix[0][3] = 0; 
//
//    rotation_matrix[1][0] = sin(rotation[X])*sin(rotation[Y])*cos(rotation[Z]) + cos(rotation[X])*sin(rotation[X]); 
//    rotation_matrix[1][1] = -sin(rotation[X])*sin(rotation[Y])*sin(rotation[Z])+cos(rotation[X])*cos(rotation[Z]); 
//    rotation_matrix[1][2] = -sin(rotation[Y])*cos(rotation[Y]);  
//    rotation_matrix[1][3] = 0; 
//
//    rotation_matrix[2][0] = -cos(rotation[X])*sin(rotation[Y])*cos(rotation[Z])+sin(rotation[X])*sin(rotation[Z]); 
//    rotation_matrix[2][1] = cos(rotation[X])*sin(rotation[Y])*sin(rotation[Z])+sin(rotation[X])*cos(rotation[Z]);
//    rotation_matrix[2][2] = cos(rotation[X])*cos(rotation[Y]); 
//    rotation_matrix[2][3] = 0; 
//
//    rotation_matrix[3][0] = 0; 
//    rotation_matrix[3][1] = 0; 
//    rotation_matrix[3][2] = 0; 
//    rotation_matrix[3][3] = 1; 


//////////////////////////
    translation_matrix[0][0] = 1; 
    translation_matrix[0][1] = 0; 
    translation_matrix[0][2] = 0; 
    translation_matrix[0][3] = translation[X];
 
    translation_matrix[1][0] = 0; 
    translation_matrix[1][1] = 1; 
    translation_matrix[1][2] = 0; 
    translation_matrix[1][3] = translation[Y];
 
    translation_matrix[2][0] = 0; 
    translation_matrix[2][1] = 0; 
    translation_matrix[2][2] = 0; 
    translation_matrix[2][3] = translation[Z];
 
    translation_matrix[3][0] = 0; 
    translation_matrix[3][1] = 0; 
    translation_matrix[3][2] = 0; 
    translation_matrix[3][3] = 1;


/////////////////////////////////

    scaling_matrix[0][0] = scaling[X]; 
    scaling_matrix[0][1] = 0; 
    scaling_matrix[0][2] = 0; 
    scaling_matrix[0][3] = 0; 
 
    scaling_matrix[1][0] = 0; 
    scaling_matrix[1][1] = scaling[Y]; 
    scaling_matrix[1][2] = 0; 
    scaling_matrix[1][3] = 0; 
 
    scaling_matrix[2][0] = 0; 
    scaling_matrix[2][1] = 0; 
    scaling_matrix[2][2] = scaling[Z]; 
    scaling_matrix[2][3] = 0; 
 
    scaling_matrix[3][0] = 0; 
    scaling_matrix[3][1] = 0; 
    scaling_matrix[3][2] = 0; 
    scaling_matrix[3][3] = 1; 
}

void Cube_3D::update_translation(float x, float y,float z){
    translation[X] = x;
    translation[Y] = y;
    translation[Z] = z;
    translation_matrix[0][3] = translation[X];
    translation_matrix[1][3] = translation[Y];
    translation_matrix[2][3] = translation[Z];
}

void Cube_3D::update_translation(float new_value, int coordinate){
    switch(coordinate)
    {
        case X:
            translation[X] = new_value;
            translation_matrix[0][3] = translation[X];
            break;
        case Y:
            translation[Y] = new_value;
            translation_matrix[1][3] = translation[Y];
            break;
        case Z:
            translation[Z] = new_value;
            translation_matrix[2][3] = translation[Z];
            break;
    }
}

void Cube_3D::update_rotation(float rx, float ry, float rz){
    rotation[X] = rx;
    rotation[Y] = ry;
    rotation[Z] = rz;
    rotation_matrix[0][0] = cos(rotation[Y])*cos(rotation[Z]); 
    rotation_matrix[0][1] = -cos(rotation[Y])*sin(rotation[Z]);
    rotation_matrix[0][2] = sin(rotation[Y]);
    rotation_matrix[0][3] = 0; 

    rotation_matrix[1][0] = sin(rotation[X])*sin(rotation[Y])*cos(rotation[Z]) + cos(rotation[X])*sin(rotation[Z]); 
    rotation_matrix[1][1] = -sin(rotation[X])*sin(rotation[Y])*sin(rotation[Z])+cos(rotation[X])*cos(rotation[Z]); 
    rotation_matrix[1][2] = -sin(rotation[X])*cos(rotation[Y]);  
    rotation_matrix[1][3] = 0; 

    rotation_matrix[2][0] = -cos(rotation[X])*sin(rotation[Y])*cos(rotation[Z])+sin(rotation[X])*sin(rotation[Z]); 
    rotation_matrix[2][1] = cos(rotation[X])*sin(rotation[Y])*sin(rotation[Z])+sin(rotation[X])*cos(rotation[Z]);
    rotation_matrix[2][2] = cos(rotation[X])*cos(rotation[Y]); 
    rotation_matrix[2][3] = 0; 

    rotation_matrix[3][0] = 0; 
    rotation_matrix[3][1] = 0; 
    rotation_matrix[3][2] = 0; 
    rotation_matrix[3][3] = 1; 
}


//void Cube_3D::update_rotation(float new_value, int coordinate){
//    switch(coordinate)
//    {
//        case X:
//            rotation[X] = new_value;
//            break;
//        case Y:
//            rotation[Y] = new_value;
//            break;
//        case Z:
//            rotation[Z] = new_value;
//            break;
//    }
//    rotation_matrix[0][0] = cos(rotation[Y])*cos(rotation[Z]); 
//    rotation_matrix[0][1] = -cos(rotation[Y])*sin(rotation[Z]);
//    rotation_matrix[0][2] = sin(rotation[Y]);
//    rotation_matrix[0][3] = 0; 
//
//    rotation_matrix[1][0] = sin(rotation[X])*sin(rotation[Y])*cos(rotation[Z]) + cos(rotation[X])*sin(rotation[X]); 
//    rotation_matrix[1][1] = -sin(rotation[X])*sin(rotation[Y])*sin(rotation[Z])+cos(rotation[X])*cos(rotation[Z]); 
//    rotation_matrix[1][2] = -sin(rotation[Y])*cos(rotation[Y]);  
//    rotation_matrix[1][3] = 0; 
//
//    rotation_matrix[2][0] = -cos(rotation[X])*sin(rotation[Y])*cos(rotation[Z])+sin(rotation[X])*sin(rotation[Z]); 
//    rotation_matrix[2][1] = cos(rotation[X])*sin(rotation[Y])*sin(rotation[Z])+sin(rotation[X])*cos(rotation[Z]);
//    rotation_matrix[2][2] = cos(rotation[X])*cos(rotation[Y]); 
//    rotation_matrix[2][3] = 0; 
//
//    rotation_matrix[3][0] = 0; 
//    rotation_matrix[3][1] = 0; 
//    rotation_matrix[3][2] = 0; 
//    rotation_matrix[3][3] = 1;  
//}

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

    #ifdef DEBUG_VECTORS
	printf("START PRINT 3D COORDINATES\n");
    #endif

    for(int i = 0; i < N_VERTEX; i++){
        transformed_vertex[i][X] =  vertex[i][X]*complete_matrix[0][0] + \
                                    vertex[i][Y]*complete_matrix[1][0] + \
                                    vertex[i][Z]*complete_matrix[2][0] + \
                                    vertex[i][W]*complete_matrix[3][0];

        transformed_vertex[i][Y] =  vertex[i][X]*complete_matrix[0][1] + \
                                    vertex[i][Y]*complete_matrix[1][1] + \
                                    vertex[i][Z]*complete_matrix[2][1] + \
                                    vertex[i][W]*complete_matrix[3][1];

        transformed_vertex[i][Z] =  vertex[i][X]*complete_matrix[0][2] + \
                                    vertex[i][Y]*complete_matrix[1][2] + \
                                    vertex[i][Z]*complete_matrix[2][2] + \
                                    vertex[i][W]*complete_matrix[3][2];

        transformed_vertex[i][W] =  vertex[i][X]*complete_matrix[0][3] + \
                                    vertex[i][Y]*complete_matrix[1][3] + \
                                    vertex[i][Z]*complete_matrix[2][3] + \
                                    vertex[i][W]*complete_matrix[3][3];

        /* Per debug, controllare se tutti i punti calcolati abbiano la stessa z*/

        #ifdef DEBUG_VECTORS
        printf("PRIMA DI NORMALIZZAZIONE Z\n");
        printf("p%d : x%f\n", i, transformed_vertex[i][X]);
        printf("p%d : y%f\n", i, transformed_vertex[i][Y]);
        printf("p%d : z%f\n", i, transformed_vertex[i][Z]);
        printf("p%d : w%f\n", i, transformed_vertex[i][W]);
        #endif

        for (int c = 0; c < 8; c++)
        {
        	transformed_vertex[c][X]/=transformed_vertex[c][W];
        	transformed_vertex[c][Y]/=transformed_vertex[c][W];
        	transformed_vertex[c][Z]/=transformed_vertex[c][W];
        	transformed_vertex[c][W]=1;

        }

        #ifdef DEBUG_VECTORS
        printf("DOPO NORMALIZZAZIONE Z\n");
        printf("p%d : x%f\n", i, transformed_vertex[i][X]);
        printf("p%d : y%f\n", i, transformed_vertex[i][Y]);
        printf("p%d : z%f\n", i, transformed_vertex[i][Z]);
        printf("p%d : w%f\n", i, transformed_vertex[i][W]);
        #endif 


                             
    }
	#ifdef DEBUG_VECTOR
    printf("END PRINT 3D COORDINATES\n");
	#endif
}

void Cube_3D::from_3D_to_2D(){
	#ifdef DEBUG_VECTOR
	printf("START PRINT 2D COORDINATES\n");
	#endif
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


        #ifdef DEBUG_VECTORS
        printf("p%d : x%f\n", i, transformed_vertex[i][X]);
        printf("p%d : y%f\n", i, transformed_vertex[i][Y]);
        printf("p%d : z%f\n", i, transformed_vertex[i][Z]);
        printf("p%d : w%f\n", i, transformed_vertex[i][W]);
        #endif


        printf("p%d - x:%d / y:%d\n",i, vertex_on_2D[i][X], vertex_on_2D[i][Y]);
    }
    printf("END PRINT 2D COORDINATES\n");
}
 
int Cube_3D::calculate_world(){
    return 1;
}

void Cube_3D::Matrix4x4MultiplyBy4x4 (float src1[4][4], float src2[4][4], float dest[4][4])
{
    dest[0][0] = src1[0][0] * src2[0][0] + src1[0][1] * src2[1][0] + src1[0][2] * src2[2][0] + src1[0][3] * src2[3][0]; 
    dest[0][1] = src1[0][0] * src2[0][1] + src1[0][1] * src2[1][1] + src1[0][2] * src2[2][1] + src1[0][3] * src2[3][1]; 
    dest[0][2] = src1[0][0] * src2[0][2] + src1[0][1] * src2[1][2] + src1[0][2] * src2[2][2] + src1[0][3] * src2[3][2]; 
    dest[0][3] = src1[0][0] * src2[0][3] + src1[0][1] * src2[1][3] + src1[0][2] * src2[2][3] + src1[0][3] * src2[3][3]; 
    dest[1][0] = src1[1][0] * src2[0][0] + src1[1][1] * src2[1][0] + src1[1][2] * src2[2][0] + src1[1][3] * src2[3][0]; 
    dest[1][1] = src1[1][0] * src2[0][1] + src1[1][1] * src2[1][1] + src1[1][2] * src2[2][1] + src1[1][3] * src2[3][1]; 
    dest[1][2] = src1[1][0] * src2[0][2] + src1[1][1] * src2[1][2] + src1[1][2] * src2[2][2] + src1[1][3] * src2[3][2]; 
    dest[1][3] = src1[1][0] * src2[0][3] + src1[1][1] * src2[1][3] + src1[1][2] * src2[2][3] + src1[1][3] * src2[3][3]; 
    dest[2][0] = src1[2][0] * src2[0][0] + src1[2][1] * src2[1][0] + src1[2][2] * src2[2][0] + src1[2][3] * src2[3][0]; 
    dest[2][1] = src1[2][0] * src2[0][1] + src1[2][1] * src2[1][1] + src1[2][2] * src2[2][1] + src1[2][3] * src2[3][1]; 
    dest[2][2] = src1[2][0] * src2[0][2] + src1[2][1] * src2[1][2] + src1[2][2] * src2[2][2] + src1[2][3] * src2[3][2]; 
    dest[2][3] = src1[2][0] * src2[0][3] + src1[2][1] * src2[1][3] + src1[2][2] * src2[2][3] + src1[2][3] * src2[3][3]; 
    dest[3][0] = src1[3][0] * src2[0][0] + src1[3][1] * src2[1][0] + src1[3][2] * src2[2][0] + src1[3][3] * src2[3][0]; 
    dest[3][1] = src1[3][0] * src2[0][1] + src1[3][1] * src2[1][1] + src1[3][2] * src2[2][1] + src1[3][3] * src2[3][1]; 
    dest[3][2] = src1[3][0] * src2[0][2] + src1[3][1] * src2[1][2] + src1[3][2] * src2[2][2] + src1[3][3] * src2[3][2]; 
    dest[3][3] = src1[3][0] * src2[0][3] + src1[3][1] * src2[1][3] + src1[3][2] * src2[2][3] + src1[3][3] * src2[3][3]; 
};

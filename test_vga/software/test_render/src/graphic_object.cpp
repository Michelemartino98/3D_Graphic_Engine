#include "../inc/config.h"

extern alt_up_pixel_buffer_dma_dev *pixel_buf_dma_dev;

Cube_3D::Cube_3D(){

    update_translation(0, 0, 0);
    update_rotation(0, 0, 0);
    update_scaling(1, 1, 1);

    
    r = imageAspectRatio * scale;
    l = -r;
    t = scale;
    b = -t;

    // set OpenGL perspective projection matrix
    projection_matrix[M(0,0)] = 2 * n / (r - l); 
    projection_matrix[M(0,1)] = 0; 
    projection_matrix[M(0,2)] = 0; 
    projection_matrix[M(0,3)] = 0; 
 
    projection_matrix[M(1,0)] = 0; 
    projection_matrix[M(1,1)] = 2 * n / (t - b); 
    projection_matrix[M(1,2)] = 0; 
    projection_matrix[M(1,3)] = 0; 
 
    projection_matrix[M(2,0)] = 0; 
    projection_matrix[M(2,1)] = 0; 
    projection_matrix[M(2,2)] = -(f + n) / (f - n); 
    projection_matrix[M(2,3)] = -1; 
 
    projection_matrix[M(3,0)] = 0; 
    projection_matrix[M(3,1)] = 0; 
    projection_matrix[M(3,2)] = -2 * f * n / (f - n); 
    projection_matrix[M(3,3)] = 0; 

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
*/

//////////////////////////
    translation_matrix[M(0,0)] = 1; 
    translation_matrix[M(0,1)] = 0; 
    translation_matrix[M(0,2)] = 0; 
    translation_matrix[M(0,3)] = translation[X];
 
    translation_matrix[M(1,0)] = 0; 
    translation_matrix[M(1,1)] = 1; 
    translation_matrix[M(1,2)] = 0; 
    translation_matrix[M(1,3)] = translation[Y];
 
    translation_matrix[M(2,0)] = 0; 
    translation_matrix[M(2,1)] = 0; 
    translation_matrix[M(2,2)] = 1; 
    translation_matrix[M(2,3)] = translation[Z];
 
    translation_matrix[M(3,0)] = 0; 
    translation_matrix[M(3,1)] = 0; 
    translation_matrix[M(3,2)] = 0; 
    translation_matrix[M(3,3)] = 1;


/////////////////////////////////

    scaling_matrix[M(0,0)] = scaling[X]; 
    scaling_matrix[M(0,1)] = 0; 
    scaling_matrix[M(0,2)] = 0; 
    scaling_matrix[M(0,3)] = 0; 
 
    scaling_matrix[M(1,0)] = 0; 
    scaling_matrix[M(1,1)] = scaling[Y]; 
    scaling_matrix[M(1,2)] = 0; 
    scaling_matrix[M(1,3)] = 0; 
 
    scaling_matrix[M(2,0)] = 0; 
    scaling_matrix[M(2,1)] = 0; 
    scaling_matrix[M(2,2)] = scaling[Z]; 
    scaling_matrix[M(2,3)] = 0; 
 
    scaling_matrix[M(3,0)] = 0; 
    scaling_matrix[M(3,1)] = 0; 
    scaling_matrix[M(3,2)] = 0; 
    scaling_matrix[M(3,3)] = 1; 
}

void Cube_3D::update_translation(float x, float y,float z){
    translation[X] = x;
    translation[Y] = y;
    translation[Z] = z;
    translation_matrix[M(0,3)] = translation[X];
    translation_matrix[M(1,3)] = translation[Y];
    translation_matrix[M(2,3)] = translation[Z];
}

void Cube_3D::update_translation(float new_value, int coordinate){
    switch(coordinate)
    {
        case X:
            translation[X] = new_value;
            translation_matrix[M(0,3)] = translation[X];
            break;
        case Y:
            translation[Y] = new_value;
            translation_matrix[M(1,3)] = translation[Y];
            break;
        case Z:
            translation[Z] = new_value;
            translation_matrix[M(2,3)] = translation[Z];
            break;
    }
}

void Cube_3D::update_rotation(float rx, float ry, float rz){
    //reference: http://www.opengl-tutorial.org/assets/faq_quaternions/index.html#Q36
    rotation[X] = rx;
    rotation[Y] = ry;
    rotation[Z] = rz;

    float a, b, c, d, e, f;
    float ad, bd;

    a = cos(rotation[X]);
    b = sin(rotation[X]);
    c = cos(rotation[Y]); 
    d = sin(rotation[Y]);
    e = cos(rotation[Z]);
    f = sin(rotation[Z]);

    ad = a*d;
    bd = b*d;

    rotation_matrix[M(0,0)] = c*e; 
    rotation_matrix[M(0,1)] = -c*f;
    rotation_matrix[M(0,2)] = d;
    rotation_matrix[M(0,3)] = 0; 

    rotation_matrix[M(1,0)] = bd*e + a*f; 
    rotation_matrix[M(1,1)] = -bd*f + a*e; 
    rotation_matrix[M(1,2)] = - b*c;  
    rotation_matrix[M(1,3)] = 0; 

    rotation_matrix[M(2,0)] = -ad*e + b*f; 
    rotation_matrix[M(2,1)] = ad*f + b*e;
    rotation_matrix[M(2,2)] = a*c;
    rotation_matrix[M(2,3)] = 0; 

    rotation_matrix[M(3,0)] = 0; 
    rotation_matrix[M(3,1)] = 0; 
    rotation_matrix[M(3,2)] = 0; 
    rotation_matrix[M(3,3)] = 1; 
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
    alt_up_pixel_buffer_dma_draw_line(pixel_buf_dma_dev,vertex_on_2D[0][X],vertex_on_2D[0][Y],vertex_on_2D[4][X],vertex_on_2D[4][Y], RED, 1);
    alt_up_pixel_buffer_dma_draw_line(pixel_buf_dma_dev,vertex_on_2D[1][X],vertex_on_2D[1][Y],vertex_on_2D[6][X],vertex_on_2D[6][Y], GREEN, 1);
    alt_up_pixel_buffer_dma_draw_line(pixel_buf_dma_dev,vertex_on_2D[1][X],vertex_on_2D[1][Y],vertex_on_2D[5][X],vertex_on_2D[5][Y], RED, 1);
    alt_up_pixel_buffer_dma_draw_line(pixel_buf_dma_dev,vertex_on_2D[2][X],vertex_on_2D[2][Y],vertex_on_2D[3][X],vertex_on_2D[3][Y], WHITE, 1);
    alt_up_pixel_buffer_dma_draw_line(pixel_buf_dma_dev,vertex_on_2D[2][X],vertex_on_2D[2][Y],vertex_on_2D[6][X],vertex_on_2D[6][Y], GREEN, 1);
    alt_up_pixel_buffer_dma_draw_line(pixel_buf_dma_dev,vertex_on_2D[3][X],vertex_on_2D[3][Y],vertex_on_2D[4][X],vertex_on_2D[4][Y], YELLOW, 1);
    alt_up_pixel_buffer_dma_draw_line(pixel_buf_dma_dev,vertex_on_2D[3][X],vertex_on_2D[3][Y],vertex_on_2D[7][X],vertex_on_2D[7][Y], YELLOW, 1);
    alt_up_pixel_buffer_dma_draw_line(pixel_buf_dma_dev,vertex_on_2D[4][X],vertex_on_2D[4][Y],vertex_on_2D[5][X],vertex_on_2D[5][Y], YELLOW, 1);
    alt_up_pixel_buffer_dma_draw_line(pixel_buf_dma_dev,vertex_on_2D[5][X],vertex_on_2D[5][Y],vertex_on_2D[7][X],vertex_on_2D[7][Y], YELLOW, 1);
    alt_up_pixel_buffer_dma_draw_line(pixel_buf_dma_dev,vertex_on_2D[6][X],vertex_on_2D[6][Y],vertex_on_2D[7][X],vertex_on_2D[7][Y], WHITE, 1);

    alt_up_pixel_buffer_dma_draw_line(pixel_buf_dma_dev,25, 70,100,100, WHITE, 1);
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
        transformed_vertex[M(X,i)] =    vertex[M(X,i)]*projection_matrix[M(0,0)] + \
                                        vertex[M(Y,i)]*projection_matrix[M(0,1)] + \
                                        vertex[M(Z,i)]*projection_matrix[M(0,2)] + \
                                        vertex[M(W,i)]*projection_matrix[M(0,3)];

        transformed_vertex[M(Y,i)] =    vertex[M(X,i)]*projection_matrix[M(1,0)] + \
                                        vertex[M(Y,i)]*projection_matrix[M(1,1)] + \
                                        vertex[M(Z,i)]*projection_matrix[M(1,2)] + \
                                        vertex[M(W,i)]*projection_matrix[M(1,3)];

        transformed_vertex[M(Z,i)] =    vertex[M(X,i)]*projection_matrix[M(2,0)] + \
                                        vertex[M(Y,i)]*projection_matrix[M(2,1)] + \
                                        vertex[M(Z,i)]*projection_matrix[M(2,2)] + \
                                        vertex[M(W,i)]*projection_matrix[M(2,3)];

        transformed_vertex[M(W,i)] =    vertex[M(X,i)]*projection_matrix[M(3,0)] + \
                                        vertex[M(Y,i)]*projection_matrix[M(3,1)] + \
                                        vertex[M(Z,i)]*projection_matrix[M(3,2)] + \
                                        vertex[M(W,i)]*projection_matrix[M(3,3)];





        /* Per debug, controllare se tutti i punti calcolati abbiano la stessa z*/

        #ifdef DEBUG_VECTORS
        printf("PRIMA DI NORMALIZZAZIONE Z\n");
        printf("p%d : x%f\n", i, transformed_vertex[M(X,i)]);
        printf("p%d : y%f\n", i, transformed_vertex[M(Y,i)]);
        printf("p%d : z%f\n", i, transformed_vertex[M(Z,i)]);
        printf("p%d : w%f\n", i, transformed_vertex[M(W,i)]);
        #endif

        for (int c = 0; c < 8; c++)
        {
        	transformed_vertex[M(X,c)]/=transformed_vertex[M(W,c)];
        	transformed_vertex[M(Y,c)]/=transformed_vertex[M(W,c)];
        	transformed_vertex[M(Z,c)]/=transformed_vertex[M(W,c)];
        	transformed_vertex[M(W,c)]=1;

        }

        #ifdef DEBUG_VECTORS
        printf("DOPO NORMALIZZAZIONE Z\n");
        printf("p%d : x%f\n", i, transformed_vertex[M(X,i)]);
        printf("p%d : y%f\n", i, transformed_vertex[M(Y,i)]);
        printf("p%d : z%f\n", i, transformed_vertex[M(Z,i)]);
        printf("p%d : w%f\n", i, transformed_vertex[M(W,i)]);
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
    	if((transformed_vertex[M(X,i)]>1) | (transformed_vertex[M(X,i)]<-1)){
    		vertex_on_2D[i][X] = 0;
    	}
    	else{
    		vertex_on_2D[i][X] = ((transformed_vertex[M(X,i)]*(X_RES/2))+(X_RES/2));
    	}
    	if((transformed_vertex[M(Y,i)]>1) | (transformed_vertex[M(Y,i)]<-1)){
    		vertex_on_2D[i][Y] = 0;
    	}
    	else{
            vertex_on_2D[i][Y] = ((transformed_vertex[M(Y,i)]*(Y_RES/2))+(Y_RES/2));
    	}


        #ifdef DEBUG_VECTORS
        printf("p%d : x%f\n", i, transformed_vertex[M(X,i)]);
        printf("p%d : y%f\n", i, transformed_vertex[M(Y,i)]);
        printf("p%d : z%f\n", i, transformed_vertex[M(Z,i)]);
        printf("p%d : w%f\n", i, transformed_vertex[M(W,i)]);
        #endif

        #ifdef DEBUG_1
        printf("p%d - x:%d / y:%d\n",i, vertex_on_2D[i][X], vertex_on_2D[i][Y]);
        #endif
    }
    #ifdef DEBUG_1
    printf("END PRINT 2D COORDINATES\n");
    #endif
}
 
int Cube_3D::calculate_world(){
    return 1;
}

void Cube_3D::Matrix4x4MultiplyBy4x4 (float src1[M(4,4)], float src2[M(4,4)], float dest[M(4,4)])
{ 
    dest[M(0,0)] = src1[M(0,0)] * src2[M(0,0)] + src1[M(0,1)] * src2[M(1,0)] + src1[M(0,2)] * src2[M(2,0)] + src1[M(0,3)] * src2[M(3,0)]; 
    dest[M(0,1)] = src1[M(0,0)] * src2[M(0,1)] + src1[M(0,1)] * src2[M(1,1)] + src1[M(0,2)] * src2[M(2,1)] + src1[M(0,3)] * src2[M(3,1)]; 
    dest[M(0,2)] = src1[M(0,0)] * src2[M(0,2)] + src1[M(0,1)] * src2[M(1,2)] + src1[M(0,2)] * src2[M(2,2)] + src1[M(0,3)] * src2[M(3,2)]; 
    dest[M(0,3)] = src1[M(0,0)] * src2[M(0,3)] + src1[M(0,1)] * src2[M(1,3)] + src1[M(0,2)] * src2[M(2,3)] + src1[M(0,3)] * src2[M(3,3)]; 
    dest[M(1,0)] = src1[M(1,0)] * src2[M(0,0)] + src1[M(1,1)] * src2[M(1,0)] + src1[M(1,2)] * src2[M(2,0)] + src1[M(1,3)] * src2[M(3,0)]; 
    dest[M(1,1)] = src1[M(1,0)] * src2[M(0,1)] + src1[M(1,1)] * src2[M(1,1)] + src1[M(1,2)] * src2[M(2,1)] + src1[M(1,3)] * src2[M(3,1)]; 
    dest[M(1,2)] = src1[M(1,0)] * src2[M(0,2)] + src1[M(1,1)] * src2[M(1,2)] + src1[M(1,2)] * src2[M(2,2)] + src1[M(1,3)] * src2[M(3,2)]; 
    dest[M(1,3)] = src1[M(1,0)] * src2[M(0,3)] + src1[M(1,1)] * src2[M(1,3)] + src1[M(1,2)] * src2[M(2,3)] + src1[M(1,3)] * src2[M(3,3)]; 
    dest[M(2,0)] = src1[M(2,0)] * src2[M(0,0)] + src1[M(2,1)] * src2[M(1,0)] + src1[M(2,2)] * src2[M(2,0)] + src1[M(2,3)] * src2[M(3,0)]; 
    dest[M(2,1)] = src1[M(2,0)] * src2[M(0,1)] + src1[M(2,1)] * src2[M(1,1)] + src1[M(2,2)] * src2[M(2,1)] + src1[M(2,3)] * src2[M(3,1)]; 
    dest[M(2,2)] = src1[M(2,0)] * src2[M(0,2)] + src1[M(2,1)] * src2[M(1,2)] + src1[M(2,2)] * src2[M(2,2)] + src1[M(2,3)] * src2[M(3,2)]; 
    dest[M(2,3)] = src1[M(2,0)] * src2[M(0,3)] + src1[M(2,1)] * src2[M(1,3)] + src1[M(2,2)] * src2[M(2,3)] + src1[M(2,3)] * src2[M(3,3)]; 
    dest[M(3,0)] = src1[M(3,0)] * src2[M(0,0)] + src1[M(3,1)] * src2[M(1,0)] + src1[M(3,2)] * src2[M(2,0)] + src1[M(3,3)] * src2[M(3,0)]; 
    dest[M(3,1)] = src1[M(3,0)] * src2[M(0,1)] + src1[M(3,1)] * src2[M(1,1)] + src1[M(3,2)] * src2[M(2,1)] + src1[M(3,3)] * src2[M(3,1)]; 
    dest[M(3,2)] = src1[M(3,0)] * src2[M(0,2)] + src1[M(3,1)] * src2[M(1,2)] + src1[M(3,2)] * src2[M(2,2)] + src1[M(3,3)] * src2[M(3,2)]; 
    dest[M(3,3)] = src1[M(3,0)] * src2[M(0,3)] + src1[M(3,1)] * src2[M(1,3)] + src1[M(3,2)] * src2[M(2,3)] + src1[M(3,3)] * src2[M(3,3)];

};

/*
void Cube_3D::chiama_le_mul(){
    test_mul4x4(test_matrix, identity_matrix, empty_matrix );
    
    printf("RISULTATO MOLTIPLICAZIONE \n");
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){

        printf("%f ,", empty_matrix[i*4+j]);
        }
        printf("\n");
    }
}
*/
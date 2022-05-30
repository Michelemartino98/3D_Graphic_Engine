#include "../inc/config.h"

extern alt_up_pixel_buffer_dma_dev *pixel_buf_dma_dev;

Graphic_engine::Graphic_engine(){




    //la traslazione inziale sull'asse z serve a spostare indietro l'oggetto nel mondo, altrimenti la camera si troverebbe nell'origine e sarebbe "dentro" il cubo(e si vede la croce delle diagonali)
    //NB: se l'oggetto finisce alle spalle della camera viene visto "all'indietro" (front e back del cubo sono invertiti)
    
    //inizializzo matrice di traslazione
    translation_matrix[M4(0,0)] = 1; 
    translation_matrix[M4(0,1)] = 0; 
    translation_matrix[M4(0,2)] = 0; 

    translation_matrix[M4(1,0)] = 0; 
    translation_matrix[M4(1,1)] = 1; 
    translation_matrix[M4(1,2)] = 0; 

    translation_matrix[M4(2,0)] = 0; 
    translation_matrix[M4(2,1)] = 0; 
    translation_matrix[M4(2,2)] = 1; 

    translation_matrix[M4(3,0)] = 0; 
    translation_matrix[M4(3,1)] = 0;
    translation_matrix[M4(3,2)] = 0;
    translation_matrix[M4(3,3)] = 1;

    update_translation(0, 0, -3);

    //inizializzo matrice di rotazione
    
    rotation_matrix[M4(0,3)] = 0;
    rotation_matrix[M4(1,3)] = 0; 
    rotation_matrix[M4(2,3)] = 0;
    rotation_matrix[M4(3,0)] = 0;
    rotation_matrix[M4(3,1)] = 0;
    rotation_matrix[M4(3,2)] = 0;
    rotation_matrix[M4(3,3)] = 1;
    update_rotation(0, 0, 0);

    //inizializzo matrice di scala
    scaling_matrix[M4(0,1)] = 0; 
    scaling_matrix[M4(0,2)] = 0; 
    scaling_matrix[M4(0,3)] = 0; 

    scaling_matrix[M4(1,0)] = 0; 
    scaling_matrix[M4(1,2)] = 0; 
    scaling_matrix[M4(1,3)] = 0; 

    scaling_matrix[M4(2,0)] = 0; 
    scaling_matrix[M4(2,1)] = 0; 
    scaling_matrix[M4(2,3)] = 0; 

    scaling_matrix[M4(3,0)] = 0; 
    scaling_matrix[M4(3,1)] = 0; 
    scaling_matrix[M4(3,2)] = 0; 
    scaling_matrix[M4(3,3)] = 1; 
    update_scaling(0.4, 0.4, 0.4);

    
    
    // set OpenGL perspective projection matrix
    r = imageAspectRatio * scale;
    l = -r;
    t = scale;
    b = -t;

    projection_matrix[M4(0,0)] = (float)(2 * n) / (r - l); 
    projection_matrix[M4(1,0)] = (float)0; 
    projection_matrix[M4(2,0)] = (float)0; 
    projection_matrix[M4(3,0)] = (float)0; 

    projection_matrix[M4(0,1)] = (float)0; 
    projection_matrix[M4(1,1)] = (float)2 * n / (t - b); 
    projection_matrix[M4(2,1)] = (float)0; 
    projection_matrix[M4(3,1)] = (float)0; 

    projection_matrix[M4(0,2)] = (float)0; 
    projection_matrix[M4(1,2)] = (float)0; 
    projection_matrix[M4(2,2)] = (float)-(f + n) / (f - n); 
    projection_matrix[M4(3,2)] = (float)-1;

    projection_matrix[M4(0,3)] = (float)0; 
    projection_matrix[M4(1,3)] = (float)0; 
    projection_matrix[M4(2,3)] = (float) -2 * f * n / (f - n);
    projection_matrix[M4(3,3)] = (float)0; 

    

   
}

void Graphic_engine::update_translation(float x, float y,float z){
    translation_matrix[M4(0,3)] = x;
    translation[X] = x;

    translation_matrix[M4(1,3)] = y;
    translation[Y] = y;

    translation_matrix[M4(2,3)] = z;
    translation[Z] = z;
}

void Graphic_engine::update_translation(float new_value, int axis){
    switch(axis)
    {
        case X:
            translation[X] = new_value;
            break;
        case Y:
            translation[Y] = new_value;
            break;
        case Z:
            translation[Z] = new_value;
            break;
    }
    update_translation(translation[X], translation[Y], translation[Z]);
}

void Graphic_engine::update_translation_relative(float relative_value, int axis ){
    switch(axis)
    {
        case X:
            translation[X] += relative_value;
            break;
        case Y:
            translation[Y] += relative_value;
            break;
        case Z:
            translation[Z] += relative_value;
            break;
    }
    update_translation(translation[X], translation[Y], translation[Z]);
}


void Graphic_engine::update_rotation(float rx, float ry, float rz){
    //reference: http://www.opengl-tutorial.org/assets/faq_quaternions/index.html#Q36
    rotation[X] = rx;
    rotation[Y] = ry;
    rotation[Z] = rz;

    float a, b, c, d, e, f;
    float ad, bd;
    //calcolo individualmente i coseni proiettori
    a = cos(rotation[X]);
    b = sin(rotation[X]);
    c = cos(rotation[Y]); 
    d = sin(rotation[Y]);
    e = cos(rotation[Z]);
    f = sin(rotation[Z]);
    
    ad = a*d;
    bd = b*d;

    rotation_matrix[M4(0,0)] = c*e; 
    rotation_matrix[M4(0,1)] = -c*f;
    rotation_matrix[M4(0,2)] = d;

    rotation_matrix[M4(1,0)] = bd*e + a*f; 
    rotation_matrix[M4(1,1)] = -bd*f + a*e; 
    rotation_matrix[M4(1,2)] = - b*c;  

    rotation_matrix[M4(2,0)] = -ad*e + b*f; 
    rotation_matrix[M4(2,1)] = ad*f + b*e;
    rotation_matrix[M4(2,2)] = a*c;
}

void Graphic_engine::update_rotation(float new_value, int axis){
    switch(axis)
    {
        case X:
            rotation[X] = new_value;
            break;
        case Y:
            rotation[Y] = new_value;
            break;
        case Z:
            rotation[Z] = new_value;
            break;
    }
    update_rotation(rotation[X], rotation[Y], rotation[Z]);
}

void Graphic_engine::update_rotation_relative(float new_value, int axis){
    switch(axis)
    {
        case X:
            rotation[X] += new_value;
            if(rotation[X]>2*M_PI)
                rotation[X]-=2*M_PI;
            break;
        case Y:
            rotation[Y] += new_value;
            if(rotation[Y]>2*M_PI)
                rotation[Y]-=2*M_PI;
            break;
        case Z:
            rotation[Z] += new_value;
            if(rotation[Z]>2*M_PI)
                rotation[Z]-=2*M_PI;
            break;
    }
    update_rotation(rotation[X], rotation[Y], rotation[Z]);
    #ifdef DEBUG_ACC
    printf("rx=%f,ry=%f,rz=%f /n",rotation[X],rotation[Y],rotation[Z]);
    #endif
}

void Graphic_engine::update_scaling(float sx, float sy, float sz){
    scaling[X] = sx;
    scaling_matrix[M4(0,0)] = sx;

    scaling[Y] = sy;
    scaling_matrix[M4(1,1)] = sy;

    scaling[Z] = sz;
    scaling_matrix[M4(2,2)] = sz;
}

void Graphic_engine::update_scaling(float new_value, int axis){
    switch(axis)
    {
        case X:
            scaling[X] = new_value;
            break;
        case Y:
            scaling[Y] = new_value;
            break;
        case Z:
            scaling[Z] = new_value;
            break;
    }
    update_scaling(scaling[X], scaling[Y], scaling[Z]);
}

void Graphic_engine::update_scaling_relative(float new_value, int axis){
    switch(axis)
    {
        case X:
            scaling[X] += new_value;
            break;
        case Y:
            scaling[Y] += new_value;
            break;
        case Z:
            scaling[Z] += new_value;
            break;
    }
    update_scaling(scaling[X], scaling[Y], scaling[Z]);
}


int Graphic_engine::display_frame(){
                printf("&cubo.n_vertex = %d\n", &cubo.n_vertex);
    printf("cubo.n_vertex = %d\n", cubo.n_vertex);
    printf("n_vertex_pnt = %d\n", n_vertex_pnt);
    printf("*n_vertex_pnt = %d\n", *n_vertex_pnt);
    printf("&n_vertex_pnt = %d\n", &n_vertex_pnt);
    //pulisco il back buffer
    alt_up_pixel_buffer_dma_clear_screen_delayed(pixel_buf_dma_dev,1);

    //disegno il cubo tramite i vari triangoli
    //disegno una linea tra i vertici dei triangoli, indicizzando la matrice vertex_on_2D con il contenuto di faces, che contiene il n. del vertice di ciascun triangolo
    for(int i=0; i < (*n_faces_pnt) ; i++){
        // { *(faces_pnt + i * 3 + A) } tutto questo serve a mettere il corretto offset per accedere a faces[i][A], da cui si ottiene il numero del vertice per indicizzare vertex_on_2D
        // alt_up_pixel_buffer_dma_draw_line_enhanced_clipping(pixel_buf_dma_dev, \
        //     vertex_on_2D[*(faces_pnt + i * 3 + A)][X],  vertex_on_2D[*(faces_pnt + i * 3 + A)][Y], \ 
        //     vertex_on_2D[*(faces_pnt + i * 3 + B)][X],vertex_on_2D[*(faces_pnt + i * 3 + B)][Y], \
        //      GREEN, 1);
        
        ////////////usando il puntatore vertex_on_2d
        alt_up_pixel_buffer_dma_draw_line_enhanced_clipping(pixel_buf_dma_dev,\
            *(vertex_on_2d_pnt + (*(faces_pnt + i * 3 + A))*2 + X), *(vertex_on_2d_pnt + (*(faces_pnt + i * 3 + A))*2 + Y),\ 
            *(vertex_on_2d_pnt + (*(faces_pnt + i * 3 + B))*2 + X), *(vertex_on_2d_pnt + (*(faces_pnt + i * 3 + B))*2 + Y),\
            GREEN, 1);

        alt_up_pixel_buffer_dma_draw_line_enhanced_clipping(pixel_buf_dma_dev,\
            *(vertex_on_2d_pnt + (*(faces_pnt + i * 3 + B))*2 + X), *(vertex_on_2d_pnt + (*(faces_pnt + i * 3 + B))*2 + Y),\
            *(vertex_on_2d_pnt + (*(faces_pnt + i * 3 + C))*2 + X), *(vertex_on_2d_pnt + (*(faces_pnt + i * 3 + C))*2 + Y),\
            GREEN, 1);

        alt_up_pixel_buffer_dma_draw_line_enhanced_clipping(pixel_buf_dma_dev,\
            *(vertex_on_2d_pnt + (*(faces_pnt + i * 3 + C))*2 + X), *(vertex_on_2d_pnt + (*(faces_pnt + i * 3 + C))*2 + Y),\
            *(vertex_on_2d_pnt + (*(faces_pnt + i * 3 + A))*2 + X), *(vertex_on_2d_pnt + (*(faces_pnt + i * 3 + A))*2 + Y),\
            GREEN, 1);
    }

    // for(int i=0; i< (*n_faces_pnt) ; i++){
    //     printf("   v: %d  ", vertex_on_2D[*(faces_pnt + i * 3 + A)][X] );
       
    // }
    // for(int i=0; i< (*n_faces_pnt) ; i++){
    //      printf("   i: %d   ", *(faces_pnt + i * 3 + A) );
    // }
    // printf("END \n\n");

    //swap del buffer, e attesa che sia eseguito
    alt_up_pixel_buffer_dma_swap_buffers(pixel_buf_dma_dev);
    while (alt_up_pixel_buffer_dma_check_swap_buffers_status(pixel_buf_dma_dev)){;}
    return 0;
}

//m[i][j]  è uguale a  *(m + i*C +j)

//vertex[V(X,i)]    *(vertex_pnt + V(X,i))

void Graphic_engine::vector_matrix_multiply(){

    #ifdef DEBUG_VECTORS
	printf("START PRINT COORDINATES\n");
    #endif

    float temp_transformed_vertex[4];
    for(int i = 0; i < (*n_vertex_pnt) ; i++){                      // vertex[V(X,i)]  ->  *(vertex_pnt + V(X,i)) modifica dell indicizzazione 
        temp_transformed_vertex[X] =    complete_matrix[M4(0,0)] * (*(vertex_pnt + V(X,i))) + \
                                        complete_matrix[M4(0,1)] * (*(vertex_pnt + V(Y,i))) + \
                                        complete_matrix[M4(0,2)] * (*(vertex_pnt + V(Z,i))) + \
                                        complete_matrix[M4(0,3)] * (*(vertex_pnt + V(W,i)));

         temp_transformed_vertex[Y] =   complete_matrix[M4(1,0)] * (*(vertex_pnt + V(X,i))) + \
                                        complete_matrix[M4(1,1)] * (*(vertex_pnt + V(Y,i))) + \
                                        complete_matrix[M4(1,2)] * (*(vertex_pnt + V(Z,i))) + \
                                        complete_matrix[M4(1,3)] * (*(vertex_pnt + V(W,i)));

         temp_transformed_vertex[Z] =   complete_matrix[M4(2,0)] * (*(vertex_pnt + V(X,i))) + \
                                        complete_matrix[M4(2,1)] * (*(vertex_pnt + V(Y,i))) + \
                                        complete_matrix[M4(2,2)] * (*(vertex_pnt + V(Z,i))) + \
                                        complete_matrix[M4(2,3)] * (*(vertex_pnt + V(W,i)));

         temp_transformed_vertex[W] =   complete_matrix[M4(3,0)] * (*(vertex_pnt + V(X,i))) +\
                                        complete_matrix[M4(3,1)] * (*(vertex_pnt + V(Y,i))) +\
                                        complete_matrix[M4(3,2)] * (*(vertex_pnt + V(Z,i))) +\
                                        complete_matrix[M4(3,3)] * (*(vertex_pnt + V(W,i)));
        #ifdef DEBUG_VECTORS
        printf("PRIMA DI NORMALIZZAZIONE Z\n");
        printf("p%d : x%f\n", i, temp_transformed_vertex[X]);
        printf("p%d : y%f\n", i, temp_transformed_vertex[Y]);
        printf("p%d : z%f\n", i, temp_transformed_vertex[Z]);
        printf("p%d : w%f\n", i, temp_transformed_vertex[W]);
        #endif

        temp_transformed_vertex[X]/=temp_transformed_vertex[W];
    	temp_transformed_vertex[Y]/=temp_transformed_vertex[W];
    	temp_transformed_vertex[Z]/=temp_transformed_vertex[W];
    	temp_transformed_vertex[W]=1;

        #ifdef DEBUG_VECTORS
        printf("DOPO NORMALIZZAZIONE Z\n");
        printf("p%d : x%f\n", i, temp_transformed_vertex[X]);
        printf("p%d : y%f\n", i, temp_transformed_vertex[Y]);
        printf("p%d : z%f\n", i, temp_transformed_vertex[Z]);
        printf("p%d : w%f\n", i, temp_transformed_vertex[W]);
        #endif

//quello che segue era la vecchia void Graphic_engine::from_3D_to_2D()
        
        #ifdef DEBUG_VECTOR
	    printf("START PRINT 2D COORDINATES\n");
	    #endif
        /*
    *   (0,0)-----------(320,0)     (-1,1)-----------(1,1)    
    *   |                   |       |                   |
    *   |       VGA         |       |       CUBO        |    
    *   |                   |       |    normalizzato   |
    *   (0,240)---------(320,240)   (-1,-1)----------(1,-1)
    */
        //vertex_on_2D[i][X] = ((temp_transformed_vertex[X]*(X_RESOLUTION/2))+(X_RESOLUTION/2));
        *(vertex_on_2d_pnt + i*2 + X) = ((temp_transformed_vertex[X]*(X_RESOLUTION/2))+(X_RESOLUTION/2));

        //il meno è necessario per mappare nell'origine della vga, il valore y=1 nelle coordinate normalizzate del cubo
        *(vertex_on_2d_pnt + i*2 + Y) = (-(temp_transformed_vertex[Y]*(Y_RESOLUTION/2))+(Y_RESOLUTION/2));
         #ifdef DEBUG_1
        printf("p%d - x:%d / y:%d\n",i, vertex_on_2D[i][X], vertex_on_2D[i][Y]);
        #endif
                                
    }
    #ifdef DEBUG_1
    printf("END PRINT COORDINATES\n");
    #endif
}

void Graphic_engine::Matrix4x4MultiplyBy4x4 (float src1[4*4], float src2[4*4], float dest[4*4])
{ 
    dest[M4(0,0)] = src1[M4(0,0)] * src2[M4(0,0)] + src1[M4(0,1)] * src2[M4(1,0)] + src1[M4(0,2)] * src2[M4(2,0)] + src1[M4(0,3)] * src2[M4(3,0)]; 
    dest[M4(0,1)] = src1[M4(0,0)] * src2[M4(0,1)] + src1[M4(0,1)] * src2[M4(1,1)] + src1[M4(0,2)] * src2[M4(2,1)] + src1[M4(0,3)] * src2[M4(3,1)]; 
    dest[M4(0,2)] = src1[M4(0,0)] * src2[M4(0,2)] + src1[M4(0,1)] * src2[M4(1,2)] + src1[M4(0,2)] * src2[M4(2,2)] + src1[M4(0,3)] * src2[M4(3,2)]; 
    dest[M4(0,3)] = src1[M4(0,0)] * src2[M4(0,3)] + src1[M4(0,1)] * src2[M4(1,3)] + src1[M4(0,2)] * src2[M4(2,3)] + src1[M4(0,3)] * src2[M4(3,3)]; 
    dest[M4(1,0)] = src1[M4(1,0)] * src2[M4(0,0)] + src1[M4(1,1)] * src2[M4(1,0)] + src1[M4(1,2)] * src2[M4(2,0)] + src1[M4(1,3)] * src2[M4(3,0)]; 
    dest[M4(1,1)] = src1[M4(1,0)] * src2[M4(0,1)] + src1[M4(1,1)] * src2[M4(1,1)] + src1[M4(1,2)] * src2[M4(2,1)] + src1[M4(1,3)] * src2[M4(3,1)]; 
    dest[M4(1,2)] = src1[M4(1,0)] * src2[M4(0,2)] + src1[M4(1,1)] * src2[M4(1,2)] + src1[M4(1,2)] * src2[M4(2,2)] + src1[M4(1,3)] * src2[M4(3,2)]; 
    dest[M4(1,3)] = src1[M4(1,0)] * src2[M4(0,3)] + src1[M4(1,1)] * src2[M4(1,3)] + src1[M4(1,2)] * src2[M4(2,3)] + src1[M4(1,3)] * src2[M4(3,3)]; 
    dest[M4(2,0)] = src1[M4(2,0)] * src2[M4(0,0)] + src1[M4(2,1)] * src2[M4(1,0)] + src1[M4(2,2)] * src2[M4(2,0)] + src1[M4(2,3)] * src2[M4(3,0)]; 
    dest[M4(2,1)] = src1[M4(2,0)] * src2[M4(0,1)] + src1[M4(2,1)] * src2[M4(1,1)] + src1[M4(2,2)] * src2[M4(2,1)] + src1[M4(2,3)] * src2[M4(3,1)]; 
    dest[M4(2,2)] = src1[M4(2,0)] * src2[M4(0,2)] + src1[M4(2,1)] * src2[M4(1,2)] + src1[M4(2,2)] * src2[M4(2,2)] + src1[M4(2,3)] * src2[M4(3,2)]; 
    dest[M4(2,3)] = src1[M4(2,0)] * src2[M4(0,3)] + src1[M4(2,1)] * src2[M4(1,3)] + src1[M4(2,2)] * src2[M4(2,3)] + src1[M4(2,3)] * src2[M4(3,3)]; 
    dest[M4(3,0)] = src1[M4(3,0)] * src2[M4(0,0)] + src1[M4(3,1)] * src2[M4(1,0)] + src1[M4(3,2)] * src2[M4(2,0)] + src1[M4(3,3)] * src2[M4(3,0)]; 
    dest[M4(3,1)] = src1[M4(3,0)] * src2[M4(0,1)] + src1[M4(3,1)] * src2[M4(1,1)] + src1[M4(3,2)] * src2[M4(2,1)] + src1[M4(3,3)] * src2[M4(3,1)]; 
    dest[M4(3,2)] = src1[M4(3,0)] * src2[M4(0,2)] + src1[M4(3,1)] * src2[M4(1,2)] + src1[M4(3,2)] * src2[M4(2,2)] + src1[M4(3,3)] * src2[M4(3,2)]; 
    dest[M4(3,3)] = src1[M4(3,0)] * src2[M4(0,3)] + src1[M4(3,1)] * src2[M4(1,3)] + src1[M4(3,2)] * src2[M4(2,3)] + src1[M4(3,3)] * src2[M4(3,3)];
};

void Graphic_engine::init_object(){
    n_vertex_pnt = &cubo.n_vertex;
    n_faces_pnt = &cubo.n_faces;

    vertex_pnt = (cubo.vertex);      // punto sempre al primo elemento della matrice, e poi lavoro con gli indici
    faces_pnt = (cubo.faces[0]);
    //vertex_on_2d_pnt = (cubo.vertex_on_2D[0]);
    printf("&cubo.n_vertex = %d\n", &cubo.n_vertex);
    printf("cubo.n_vertex = %d\n", cubo.n_vertex);
    printf("n_vertex_pnt = %d\n", n_vertex_pnt);
    printf("*n_vertex_pnt = %d\n", *n_vertex_pnt);
    vertex_on_2d_pnt = new int[(*n_vertex_pnt) * 2];
}

void Graphic_engine::change_object(){

    uint16_t    edge_capture_k1;
    static int  index_figure = 2;

    edge_capture_k1 =  IORD_ALTERA_AVALON_PIO_EDGE_CAP(KEY_BASE) & BIT(KEY1);
    
    if( edge_capture_k1 ) {
        edge_capture_k1 = 0;
        IOWR_ALTERA_AVALON_PIO_EDGE_CAP(KEY_BASE, BIT(KEY1));
        switch (index_figure)
        {   
            //per aggiungere oggetti modificare anche N_OBJECT 
            case 1:
                delete []vertex_on_2d_pnt;
                n_vertex_pnt = &cubo.n_vertex;
                n_faces_pnt = &cubo.n_faces;
                vertex_pnt = cubo.vertex;      
                faces_pnt = (cubo.faces[0]);
                vertex_on_2d_pnt = new int[(*n_vertex_pnt) * 2];
                break;
            case 2:
                delete []vertex_on_2d_pnt;
                n_vertex_pnt = &teapot.n_vertex;
                n_faces_pnt = &teapot.n_faces;
                vertex_pnt = teapot.vertex;     
                faces_pnt = (teapot.faces[0]);
                vertex_on_2d_pnt = new int[(*n_vertex_pnt) * 2];
                break;
            // case 3:
            //     delete []vertex_on_2d_pnt;
            //     n_vertex_pnt = &sphere.n_vertex;
            //     n_faces_pnt = &sphere.n_faces;
            //     vertex_pnt = sphere.vertex;      
            //     faces_pnt = (sphere.faces[0]);
            //     vertex_on_2d_pnt = new int[(*n_vertex_pnt) * 2];
            //     break;
            case 4:
                delete []vertex_on_2d_pnt;
                n_vertex_pnt = &sphericon.n_vertex;
                n_faces_pnt = &sphericon.n_faces;
                vertex_pnt = sphericon.vertex;      
                faces_pnt = (sphericon.faces[0]);
                vertex_on_2d_pnt = new int[(*n_vertex_pnt) * 2];
                break;            
            
            default:
                break;
        }
        
        index_figure = (index_figure >= N_OBJECT) ? 1 : (index_figure + 1);
    }
    
} 
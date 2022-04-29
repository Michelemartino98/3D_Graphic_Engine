#ifndef GRAPHIC_OBJECT_H_
#define GRAPHIC_OBJECT_H_

#include "./config.h"

#define N_VERTEX 8
//user type definition
typedef float matrix4_t[16];



class Cube_3D{

        float position[3];      //x,y,z
        float rotation[3];      //rx,ry,rz
        float scaling[3];
        float projection_matrix[4][4];

        float n = 0.1; 
        float f = 100; 
        float angleOfView = 90;
        float imageAspectRatio = 4/3;
        float scale = 0.1; // tan(angleOfView * 0.5 * M_PI / 180) * n;  
        float r, l, t, b;  
        //struttura dati che contiene i vertici originali del solido sui quali applico le traslazioni


        // float vertex[N_VERTEX][4]={ {-1,  1,  1, 0},
        //                { 1,  1,  1, 0},
        //                {-1, -1,  1, 0},
        //                {-1, -1, -1, 0},
        //                {-1,  1, -1, 0},
        //                { 1,  1, -1, 0},
        //                { 1, -1,  1, 0},
        //                { 1, -1, -1, 0}};

        //contiene i vertici trasformati, ma sempre 3D
        float transformed_vertex[N_VERTEX][4];
        //struttura dati che contiene le coordinate dei vertici del solido proiettati in 2D, da mandare direttamente a schermo. 
        //Viene inizializzata quando viene costruita la classe moltiplicando vertex per le matrici di rotazione, proiezione, etc...
        uint16_t vertex_on_2D[N_VERTEX][2];
        
    public:
        Cube_3D();

        float vertex[N_VERTEX][4]={ {-0.5,  0.5,   0.5, 1},
                       {  0.5,   0.5,   0.5, 1},
                       {- 0.5, - 0.5,   0.5, 1},
                       {- 0.5, - 0.5, - 0.5, 1},
                       {- 0.5,   0.5, - 0.5, 1},
                       {  0.5,   0.5, - 0.5, 1},
                       {  0.5, - 0.5,   0.5, 1},
                       {  0.5, - 0.5, - 0.5, 1}};




        void update_position(float, float, float);
        void update_rotation(float, float, float);
        void update_scaling(float, float, float);
        void vector_matrix_multiply();
        void from_3D_to_2D();
        int calculate_world();
        // parte dalla matrice trasformed_vertex e lo spiattella in 2D          può aver senso farla privata...
        int apply_projection();
        //ritorna 0 quando ha effettivamente fatto lo swap del buffer
        int display_frame();
};


#endif //GRAPHIC_OBJECT_H_

//     float n = 0.1; 
//     float f = 100; 
//     float angleOfView = 90;
//     float imageAspectRatio = 4/3;
//     float scale = tan(angleOfView * 0.5 * M_PI / 180) * n;      ->0.1
//     r = imageAspectRatio * scale;       
//     l = -r; 
//     t = scale;
//     b = -t; 

   

    //      // set OpenGL perspective projection matrix
    // M[0][0] = 2 * n / (r - l); 
    // M[0][1] = 0; 
    // M[0][2] = 0; 
    // M[0][3] = 0; 
 
    // M[1][0] = 0; 
    // M[1][1] = 2 * n / (t - b); 
    // M[1][2] = 0; 
    // M[1][3] = 0; 
 
    // M[2][0] = 0; 
    // M[2][1] = 0; 
    // M[2][2] = -(f + n) / (f - n); 
    // M[2][3] = -1; 
 
    // M[3][0] = 0; 
    // M[3][1] = 0; 
    // M[3][2] = -2 * f * n / (f - n); 
    // M[3][3] = 0; 

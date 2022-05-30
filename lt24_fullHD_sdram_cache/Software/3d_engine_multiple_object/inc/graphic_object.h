#ifndef GRAPHIC_OBJECT_H_
#define GRAPHIC_OBJECT_H_

#include "./config.h"

#define N_OBJECT 2
#define N_VERTEX 8
// #define N_FACES 12

/*
 * viene impiegato un sistema destrogiro,
 * la camera punta verso l'asse Z negativo, 
 * il piano di proiezione è su Z=0,
 * i vettori tridimensionali sono su colonna, ovvero |X|
 *                                                   |Y|
 *                                                   |Z|
 *                                                   |W|
 * lo spazio oggetto è fisso e immutabile
 * 
 */


/*
 * COORDINATE CUBO
 *
 *       7--------6
 * 		/|       /|
 * 		3-------2 |
 *      | |     | |
 *      | 4-----|-5
 *      |/      |/
 *      0-------1
 *
 *
 */

/*
 * SISTEMA DI RIFERIMENTO
 * la telecamera punta verso Z-
 *        Y+
 *        |
 * 		  |
 * 		  |
 * 		  O-----X+
 * 	    /
 * 	   /
 * 	  Z+
 *
 */

/*
 * SISTEMA DI RIFERIMENTO DE-10Lite
 *
 * 	  ^ Y+
 *    |
 *    |  ---------------__
 *    |  |             |__|  SOCKET_VGA
 *    |  | BOARD_TOP   |
 *    |  |             |
 *    |  ---------------
 *    @---------------------> X+
 *    Z+
 */

class Graphic_engine{

        //puntatori per cambio figura
        const uint16_t* n_vertex_pnt;
        const uint16_t* n_faces_pnt;
        float* vertex_pnt;  //ci sta dichiararlo const ??
        uint16_t* faces_pnt; //ci sta dichiararlo const ??
        
        //parametri per controllo matrici
        float translation[3];      //x,y,z
        float rotation[3];      //rx,ry,rz
        float scaling[3];

        //parametri per la matrice di proiezione
        float n = 0.1; 
        float f = 100;
        float r, l, t, b; 
        float angleOfView = 45;
        float imageAspectRatio = (float)4/3;
        float scale = tan(angleOfView * 0.5 * M_PI / 180) * n; //= 0.1;          //tan(angleOfView * 0.5 * M_PI / 180) * n;  
          
        
        //struttura dati che contiene le coordinate dei vertici del solido proiettati in 2D, da mandare direttamente a schermo. 
        //Viene inizializzata quando viene costruita la classe moltiplicando vertex per le matrici di rotazione, proiezione, etc...
        
        //int vertex_on_2D[N_VERTEX][2];
        int* vertex_on_2d_pnt;

        float projection_matrix[4*4];
        float rotation_matrix[4*4];
        float translation_matrix[4*4];
        float scaling_matrix[4*4];
         //matrici di appoggio per le varie moltiplicazioni
        float proj_trasl[4*4];
        float proj_trasl_rot[4*4];
        //matrice finale che rappresenta l'intera trasformazione
        float complete_matrix[4*4];

        //useful matrix for debug
        float empty_matrix[4*4]={0};
        float identity_matrix[4*4]={1,0,0,0,
                                    0,1,0,0,
                                    0,0,1,0,
                                    0,0,0,1};

        void Matrix4x4MultiplyBy4x4(float *, float *, float *);
        //motliplicazione della matrice finale per ciascun vertice
        void vector_matrix_multiply();
        // parte dalla matrice trasformed_vertex e lo spiattella in 2D   
        void from_3D_to_2D();
    

    public:
       

        Graphic_engine();

        //#define M8(x,y) (x*N_VERTEX+y)
        inline int V(int x, int y){ return x * (int)(*n_vertex_pnt) + y; }
        //funzioni overloaded per modificare tutti i parametri oppure solamente quelli di un asse
        void update_translation(float, float, float);
        void update_translation(float, int);

        void update_rotation(float, float, float);
        void update_rotation(float, int);

        void update_scaling(float, float, float);
        void update_scaling(float, int);

        void update_translation_relative(float, int);
        void update_rotation_relative(float, int);
        void update_scaling_relative(float, int);

        //funzione per calcolo trasformazioni controllate dall'accelerometro
        void update_acc_trsformation();
        
        //una funzione inline pare non possa avere prototipo e definizione su file diversi, quindi la definisco qui
        inline void calculate_rendering(){
            Matrix4x4MultiplyBy4x4(projection_matrix, translation_matrix, proj_trasl);
            Matrix4x4MultiplyBy4x4(proj_trasl, rotation_matrix, proj_trasl_rot);
            Matrix4x4MultiplyBy4x4(proj_trasl_rot, scaling_matrix, complete_matrix);
            vector_matrix_multiply();
            //from_3D_to_2D();
        }
        //ritorna 0 quando ha effettivamente fatto lo swap del buffer
        int display_frame();
        void change_object();
};



struct {
    #define N_VERTEX_CUBO 8
    #define N_FACES_CUBO 12
    
     const uint16_t n_vertex = N_VERTEX_CUBO; 
     const uint16_t n_faces = N_FACES_CUBO; 
    float vertex[N_VERTEX_CUBO*4] = {   -1,  1,   1, -1, -1,  1,  1, -1,
                                        -1, -1,   1,  1, -1, -1,  1,  1,
                                        1,  1,   1,  1, -1, -1, -1, -1,
                                        1,  1,   1,  1,  1,  1,  1,  1 };
    uint16_t faces[N_FACES_CUBO][3] = {  {0,  2, 3},
                                {0, 1, 2},
                                {1, 5, 6},
                                { 1,2 ,6 },
                                { 3,2 ,7 },
                                { 2,7 ,6 },
                                { 0,3 ,7 },
                                { 0, 4,7 },
                                { 0, 1,5 },
                                {0,4 ,5},                                        
                                {4,5 ,6},
                                {4,7 ,6}                                        
                                };
    int vertex_on_2D[N_VERTEX_CUBO][2];
}cubo;


struct{
    #define N_VERTEX_CUBO2 8
    #define N_FACES_CUBO2 12
    uint16_t const n_vertex = N_VERTEX_CUBO2; 
    uint16_t const n_faces = N_FACES_CUBO2; 
    float vertex[N_VERTEX_CUBO2*4] = {  -0.5,  0.5,  0.5, -0.5, -0.5,  0.5,  0.5, -0.5,
                                        -0.5, -0.5,  0.5,  0.5, -0.5, -0.5,  0.5,  0.5,
                                         0.5,  0.5,  0.5,  0.5, -0.5, -0.5, -0.5, -0.5,
                                         1,  1,  1,  1,  1,  1,  1,  1 };
    uint16_t faces[N_FACES_CUBO2][3] = {  {0,  2, 3},
                                {0, 1, 2},
                                {1, 5, 6},
                                { 1,2 ,6 },
                                { 3,2 ,7 },
                                { 2,7 ,6 },
                                { 0,3 ,7 },
                                { 0, 4,7 },
                                { 0, 1,5 },
                                {0,4 ,5},                                        
                                {4,5 ,6},
                                {4,7 ,6}                                        
                                };
    int vertex_on_2D[N_VERTEX_CUBO2][2];
}cubo2;


#endif //GRAPHIC_OBJECT_H_


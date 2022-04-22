#ifndef GRAPHIC_OBJECT_H_
#define GRAPHIC_OBJECT_H_

#define N_VERTEX 8
//user type definition
typedef float matrix4_t[16];



class Cube_3D{


        float position[3];      //x,y,z
        float rotation[3];      //rx,ry,rz
        float scaling[3];
        float vertex[N_VERTEX][4]={ {-1,  1,  1, 0},
                       { 1,  1,  1, 0},
                       {-1, -1,  1, 0},
                       {-1, -1, -1, 0},
                       {-1,  1, -1, 0},
                       { 1,  1, -1, 0},
                       { 1, -1,  1, 0},
                       { 1, -1, -1, 0}};
    public:
        Cube_3D();
        void update_position(float, float,float);
        void update_rotation(float, float, float);
        void update_scaling(float, float, float);

};

#endif //GRAPHIC_OBJECT_H_

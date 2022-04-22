#include "../inc/config.h"



Cube_3D::Cube_3D(){
    //vertex[0][]={-1,  1,  1, 0};
    //vertex[1][]={ 1,  1,  1, 0};
    //vertex[2][]={-1, -1,  1, 0};
    //vertex[3][]={-1, -1, -1, 0};
    //vertex[4][]={-1,  1, -1, 0};
    //vertex[5][]={ 1,  1, -1, 0};
    //vertex[6][]={ 1, -1,  1, 0};
    //vertex[7][]={ 1, -1, -1, 0};



    update_position(0, 0, 0);
    update_rotation(0, 0, 0);
    update_scaling(1, 1, 1);
    
}

void Cube_3D::update_position(float x, float y,float z){
    position[0] = x;
    position[1] = y;
    position[2] = z;
}

void Cube_3D::update_rotation(float rx, float ry, float rz){
    rotation[0] = rx;
    rotation[1] = ry;
    rotation[2] = rz;
}

void Cube_3D::update_scaling(float sx, float sy, float sz){
    scaling[0] = sx;
    scaling[1] = sy;
    scaling[2] = sz;
}

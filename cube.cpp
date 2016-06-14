#include "cube.h"

Cube::Cube(QVector3D pos, float width, float height, float length)
{
    this->pos = pos;
    this->width = width;
    this->height = height;
    this->length = length;
    red = 1.0;
    green = 1.0;
    blue = 1.0;
}

Cube::~Cube(){
}

void Cube::draw(){
    // punkt rechts unten vorne
    float x = pos.x() + (width/2.0);
    float y = pos.y() - (height/2.0);
    float z = pos.z() + (length/2.0);

    float faces[6][4][3] = {
        {{x, y, z}, {x, y+height, z}, {x-width, y+height, z}, {x-width, y, z}}, //FRONT
        {{x, y, z-length}, {x, y+height, z-length}, {x-width, y+height, z-length}, {x-width, y, z-length}}, //BACK2
        {{x, y, z}, {x, y, z-length}, {x, y+height, z-length}, {x, y+height, z}}, // RIGHT
        {{x-width, y, z}, {x-width, y+height, z}, {x-width, y+height, z-length}, {x-width, y, z-length}}, // LEFT
        {{x, y+height, z}, {x, y+height, z-length}, {x-width, y+height, z-length}, {x-width, y+height, z}}, //TOP
        {{x, y, z}, {x, y, z-length}, {x-width, y, z-length}, {x-width, y, z}} // BOTTOM
    };

    /*float colors[6][3] = {
        {0.6, 0.6, 0.6}, //FRONT
        {1.0, 0.0, 0.0}, //BACK
        {0.0, 0.0, 1.0}, //RIGHT
        {0.0, 1.0, 0.0}, //LEFT
        {0.0, 1.0, 1.0}, //TOP
        {1.0, 1.0, 1.0} //BOTTOM
    };*/

    float normals[6][3] = {
        {0.0, 0.0, 1.0}, //FRONT
        {0.0, 0.0, -1.0}, //BACK
        {1.0, 0.0, 0.0}, //RIGHT
        {-1.0, 0.0, 0.0}, //LEFT
        {0.0, 1.0, 0.0}, //TOP
        {0.0, -1.0, 0.0} //BOTTOM
    };

    glBegin(GL_QUADS);
        for(int i = 0; i < 6; i++){
            glColor3f(red, green, blue);
            glNormal3f(normals[i][0], normals[i][1], normals[i][2]);
            glVertex3f(faces[i][0][0], faces[i][0][1], faces[i][0][2]);
            glVertex3f(faces[i][1][0], faces[i][1][1], faces[i][1][2]);
            glVertex3f(faces[i][2][0], faces[i][2][1], faces[i][2][2]);
            glVertex3f(faces[i][3][0], faces[i][3][1], faces[i][3][2]);
        }
    glEnd();
}

void Cube::setColor(float red, float green, float blue){
    this->red = red;
    this->green = green;
    this->blue = blue;
}

void Cube::setPos(QVector3D pos){
    this->pos = pos;
}

void Cube::setWidth(float width){
    this->width = width;
}

void Cube::setHeight(float height){
    this->height = height;
}

void Cube::setLength(float length){
    this->length = length;
}

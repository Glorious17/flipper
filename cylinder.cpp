#include "cylinder.h"
#include <cmath>

Cylinder::Cylinder(QVector3D pos, float radius, float height)
{
    this->pos = pos;
    this->radius = radius;
    this->height = height;

    red = 1.0;
    green = 1.0;
    blue = 1.0;
}

Cylinder::Cylinder(){

}

Cylinder::~Cylinder(){
}

void Cylinder::draw(){

    int strips = 45; //wie viele "ecken" soll der zylinder haben

    float delta = (2.0f * M_PI)/strips;
    float step;
    float x;
    float y;
    float z;

    glColor3f(red, green, blue);

    /*//Clyinder Top
    glBegin(GL_POLYGON);
    glNormal3f(0.0, 1.0, 0.0);
    for(int i = 0; i < strips; i++){
        step = i*delta;
        x = pos.x() + radius * cosf(step);
        y = pos.y() + (height/2.0);
        z = pos.z() + radius * sinf(step);
        glVertex3f(x, y, z);
    }
    glEnd();*/

    //Cylinder Bottom
    glBegin(GL_POLYGON);
    glNormal3f(0.0, -1.0, 0.0);
    for(int i = 0; i < strips; i++){
        step = i*delta;
        x = pos.x() + radius * cosf(step);
        y = pos.y() - (height/2.0);
        z = pos.z() + radius * sinf(step);
        glVertex3f(x, y, z);
    }
    glEnd();

    float xn;
    float zn;
    glColor4f(red, green, blue, 0.6);
    //Cylinder Sides
    glBegin(GL_QUAD_STRIP);
    for(int i = 0; i <= strips; i++){

        step = i*delta;

        xn = cosf(step);
        zn = sinf(step);

        x = pos.x() + radius * xn;
        z = pos.z() + radius * zn;

        glNormal3f(xn, 0.0, zn);

        glVertex3f(x, pos.y() + (height/2.0), z);
        glVertex3f(x, pos.y() - (height/2.0), z);
    }
    glEnd();
}

//Setter---------------------------------------------------

void Cylinder::setColor(float red, float green, float blue){
    this->red = red;
    this->green = green;
    this->blue = blue;
}

void Cylinder::setPos(QVector3D pos){
    this->pos = pos;
}

void Cylinder::setHeight(float height){
    this->height = height;
}

void Cylinder::setRadius(float radius){
    this->radius = radius;
}

//Getter---------------------------------------------------

QVector3D Cylinder::getPos(){
    return pos;
}

float Cylinder::getHeight(){
    return height;
}

float Cylinder::getRadius(){
    return radius;
}









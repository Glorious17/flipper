#include "cylinder.h"

Cylinder::Cylinder(QVector3D pos, float radius, float height)
{
    this->pos = pos;
    this->radius = radius;
    this->height = height;


    strips = 45;

    red = 1.0;
    green = 1.0;
    blue = 1.0;
}

Cylinder::~Cylinder(){
}

void Cylinder::draw(){

    float step = (2.0f * M_PI)/strips;
    float x;
    float y;
    float z;

    glColor3f(red, green, blue);

    //Clyinder Top
    glBegin(GL_POLYGON);
    glNormal3f(0.0, 1.0, 0.0);
    for(float i = 0; i <= 2.0f*M_PI; i += step){
        x = pos.x() + radius * cosf(i);
        y = pos.y() + (height/2.0);
        z = pos.z() + radius * sinf(i);
        glVertex3f(x, y, z);
    }
    glEnd();

    //Cylinder Bottom
    glBegin(GL_POLYGON);
    glNormal3f(0.0, -1.0, 0.0);
    for(float i = 0; i <= 2.0f*M_PI; i += step){
        x = pos.x() + radius * cosf(i);
        y = pos.y() - (height/2.0);
        z = pos.z() + radius * sinf(i);
        glVertex3f(x, y, z);
    }
    glEnd();

    float xn;
    float zn;
    //Cylinder Sides
    glBegin(GL_QUAD_STRIP);
    for(float i = 0; i <= (2.0f*M_PI); i += step){

        qDebug("i: %f | 2.0f*M_PI: %f", i, (2.0f*M_PI));


        xn = cosf(i);
        zn = sinf(i);

        x = pos.x() + radius * xn;
        z = pos.z() + radius * zn;

        glNormal3f(xn, 0.0, zn);

        glVertex3f(x, pos.y() + (height/2.0), z);
        glVertex3f(x, pos.y() - (height/2.0), z);
    }
    glEnd();
}

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

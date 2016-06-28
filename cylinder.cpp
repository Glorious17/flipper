#include "cylinder.h"
#include <cmath>

Cylinder::Cylinder(QVector3D pos, float radius, float height)
{
    this->pos = pos;
    axis = QVector3D(0.0, 1.0, 0.0);
    this->radius = radius;
    this->height = height;
    xRot = 0.0;
    yRot = 0.0;
    zRot = 0.0;

    rotMatrix = QMatrix4x4();
    tranMatrix = QMatrix4x4();
    tranMatrix.translate(pos);

    red = 1.0;
    green = 1.0;
    blue = 1.0;
}

Cylinder::Cylinder(){}
Cylinder::~Cylinder(){}

void Cylinder::draw(){

    glPushMatrix();

    glTranslatef(pos.x(), pos.y(), pos.z());

    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);
    glRotatef(zRot, 0.0, 0.0, 1.0);

    int strips = 45; //wie viele "ecken" soll der zylinder haben

    float delta = (2.0f * M_PI)/strips;
    float step;
    float x;
    float y;
    float z;

    glColor3f(red, green, blue);

    //Clyinder Top-------------------------------
    glBegin(GL_POLYGON);
    glNormal3f(0.0, 1.0, 0.0);
    for(int i = 0; i < strips; i++){
        step = i*delta;
        x = radius * cosf(step);
        y = (height/2.0);
        z = radius * sinf(step);
        glVertex3f(x, y, z);
    }
    glEnd();
    //-------------------------------Clyinder Top

    //Cylinder Bottom----------------------------
    glBegin(GL_POLYGON);
    glNormal3f(0.0, -1.0, 0.0);
    for(int i = 0; i < strips; i++){
        step = i*delta;
        x = radius * cosf(step);
        y = -(height/2.0);
        z = radius * sinf(step);
        glVertex3f(x, y, z);
    }
    glEnd();
    //----------------------------Cylinder Bottom

    float xn;
    float zn;

    //Cylinder Sides-----------------------------
    glBegin(GL_QUAD_STRIP);
    for(int i = 0; i <= strips; i++){

        step = i*delta;

        xn = cosf(step);
        zn = sinf(step);

        x = radius * xn;
        z = radius * zn;

        glNormal3f(xn, 0.0, zn);

        glVertex3f(x, (height/2.0), z);
        glVertex3f(x, -(height/2.0), z);
    }
    glEnd();
    //-----------------------------Cylinder Sides

    glPopMatrix();
}

QVector3D Cylinder::getGlobalCoordinatesOfPoint(QVector3D local){
    QMatrix4x4 matrix = tranMatrix * rotMatrix;
    QVector3D global = matrix * (local);
    return global;
}

QVector3D Cylinder::getGlobalCoordinatesOfVector(QVector3D local){
    QVector3D global = rotMatrix * (local);
    return global;
}

void Cylinder::fadeToColor(float redFade, float greenFade, float blueFade){
    this->redFade = redFade;
    this->greenFade = greenFade;
    this->blueFade = blueFade;
}

//Setter---------------------------------------------------

void Cylinder::setColor(float red, float green, float blue){
    this->red = red;
    this->green = green;
    this->blue = blue;
    redFade = red;
    greenFade = green;
    blueFade = blue;
}

void Cylinder::setPos(QVector3D pos){
    QVector3D dPos = QVector3D(pos.x() - this->pos.x(), pos.y() - this->pos.y(), pos.z() - this->pos.z());
    tranMatrix.translate(dPos);

    this->pos = pos;
}

void Cylinder::setRotation(float xRot, float yRot, float zRot){

    float dxRot = xRot - this->xRot;
    float dyRot = yRot - this->yRot;
    float dzRot = zRot - this->zRot;
    rotMatrix.rotate(dxRot, 1.0, 0.0, 0.0);
    rotMatrix.rotate(dyRot, 0.0, 1.0, 0.0);
    rotMatrix.rotate(dzRot, 0.0, 0.0, 1.0);

    this->xRot = xRot;
    this->yRot = yRot;
    this->zRot = zRot;
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









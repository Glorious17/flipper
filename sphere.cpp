#include "sphere.h"
#include "cube.h"
#include <cmath>

bool fading = false;

Sphere::Sphere(QVector3D pos, float radius, float kg)
{
    this->pos = pos;
    this->direction = QVector3D(0.0, 0.0, 0.0);
    this->radius = radius;
    this->kg = kg;

    red = 1.0;
    green = 1.0;
    blue = 1.0;
}

Sphere::Sphere(){

}

Sphere::~Sphere()
{
}

void Sphere::draw(){


    int latitudes = 90;         //breitengrade = horizontal
    int longtitudes = 90;       //längengrade = vertikal

    //https://de.wikipedia.org/wiki/Kugel

    float hor_delta = (2.0f * M_PI)/float(latitudes);  //delta_theta = hor_delta
    float ver_delta = (M_PI)/float(longtitudes);       //delta_phi = ver_delta

    if(red < redFade) red+=0.01;
    if(green < greenFade) green+=0.01;
    if(blue < blueFade) blue+=0.01;
    if(red > redFade) red-=0.01;
    if(green > greenFade) green-=0.01;
    if(blue > blueFade) blue-=0.01;


    glColor3f(red, green, blue);
    for(float i = 0.0; i < 1.0f * M_PI; i += ver_delta){
        glBegin(GL_QUAD_STRIP);
        for(float j = 0.0; j <= 2.0f*M_PI + hor_delta; j += hor_delta){

            float xn = sinf(i) * cosf(j);
            float yn = sinf(i) * sinf(j);
            float zn = cosf(i);

            glNormal3f(xn, yn, zn);
            glVertex3f(pos.x() + radius * xn, pos.y() + radius * yn, pos.z() + radius * zn);

            float xn2 = sinf(i+ver_delta) * cosf(j);
            float yn2 = sinf(i+ver_delta) * sinf(j);
            float zn2 = cosf(i+ver_delta);

            glVertex3f(pos.x() + radius * xn2, pos.y() + radius * yn2, pos.z() + radius * zn2);
        }
        glEnd();
    }
}

void Sphere::fadeToColor(float redFade, float greenFade, float blueFade){ //Für einen schönen Farbübergang
    this->redFade = redFade;
    this->greenFade = greenFade;
    this->blueFade = blueFade;
}

//Setter---------------------------------------------------

void Sphere::setColor(float red, float green, float blue){
    this->red = red;
    this->green = green;
    this->blue = blue;
    redFade = red;
    greenFade = green;
    blueFade = blue;
}

void Sphere::setPos(QVector3D pos){
    this->pos = pos;
}

void Sphere::setDirection(QVector3D direction){
    this->direction = direction;
}

void Sphere::setRadius(float radius){
    this->radius = radius;
}

void Sphere::setMass(float kg){
    this->kg = kg;
}

//Getter---------------------------------------------------

QVector3D Sphere::getPos(){
    return pos;
}

QVector3D Sphere::getDirection(){
    return direction;
}

float Sphere::getRadius(){
    return radius;
}

float Sphere::getMass(){
    return kg;
}

float Sphere::getArea(){
    return 4 * M_PI * pow(radius, 2);
}


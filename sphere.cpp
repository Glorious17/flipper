#include "sphere.h"
#include "cube.h"
#include <cmath>

Sphere::Sphere(QVector3D pos, float radius)
{
    this->pos = pos;
    this->direction = QVector3D(0.0, 0.0, 0.0);
    this->radius = radius;

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

    float hor_delta = (2.0f * M_PI)/float(latitudes);  //delta_theta
    float ver_delta = (M_PI)/float(longtitudes);       //delta_phi

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

void Sphere::updatePosition(){

    if(direction.y() > -0.981f){
        direction -= QVector3D(0.0, 0.00981f, 0.0);
    }
    pos += direction;
}

bool Sphere::checkIntersection(Cube& cube, float& lamda){

    /*//checking bounding box

    QVector3D linksUnten = getGlobalCoordinatesOfPoint(QVector3D(-width/2.0, -height/2.0, 0.0));
    QVector3D linksOben = getGlobalCoordinatesOfPoint(QVector3D(-width/2.0, height/2.0, 0.0));
    QVector3D rechtsUnten = getGlobalCoordinatesOfPoint(QVector3D(width/2.0, -height/2.0, 0.0));
    QVector3D rechtsOben = getGlobalCoordinatesOfPoint(QVector3D(width/2.0, height/2.0, 0.0));

    if((spherePos.x() > rechtsOben.x() && spherePos.x() > rechtsUnten.x()) ||
            (spherePos.x() < linksOben.x() && spherePos.x() < linksUnten.x()) ||
            (spherePos.y() > linksOben.y() && spherePos.y() > rechtsOben.y()) ||
            (spherePos.y() < linksUnten.y() && spherePos.y() < rechtsUnten.y())){
        return false;
    }

    qDebug("is in");*/

    //TOP PLANE

    QVector3D x = cube.getGlobalCoordinatesOfPoint(QVector3D(0.0, cube.getHeight()/2.0 + radius, 0.0));
    QVector3D xn = cube.getGlobalCoordinatesOfVector(QVector3D(0.0, 1.0, 0.0));

    float skalarProdukt = QVector3D::dotProduct(direction, xn);

    if(skalarProdukt == 0.0){               //Wenn das Skalaprodukt 0 ist, sind die Vektoren senkrecht zueinander
        return false;
    }

    lamda = (QVector3D::dotProduct(xn, x - pos)/skalarProdukt);

    if(lamda < 0){
        return false;
    }
    return true;
}

//Setter---------------------------------------------------

void Sphere::setColor(float red, float green, float blue){
    this->red = red;
    this->green = green;
    this->blue = blue;
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






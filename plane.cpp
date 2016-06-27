#include "plane.h"

Plane::Plane(QVector3D pos, QVector3D normal, float length)
{
    this->pos = pos;
    this->normal = normal;
    this->length = length;
}

Plane::Plane(){}
Plane::~Plane(){}

void Plane::setPos(QVector3D pos){
    this->pos = pos;
}

void Plane::setNormal(QVector3D normal){
    this->normal = normal;
}

QVector3D Plane::getPos(){
    return pos;
}

QVector3D Plane::getNormal(){
    return normal;
}

float Plane::getLength(){
    return length;
}



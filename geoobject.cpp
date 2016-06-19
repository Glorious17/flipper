#include "geoobject.h"

GeoObject::GeoObject()
{
    red = 1.0;
    green = 1.0;
    blue = 1.0;
}

GeoObject::~GeoObject(){
}

void GeoObject::draw(){}

//Setter---------------------------------------------------

void GeoObject::setColor(float red, float green, float blue){
    this->red = red;
    this->green = green;
    this->blue = blue;
}

void GeoObject::setPos(QVector3D pos){
    this->pos = pos;
}

//Getter---------------------------------------------------

QVector3D GeoObject::getPos(){
    return pos;
}






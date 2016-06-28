#ifndef SPHERE_H
#define SPHERE_H

#include <QOpenGLFunctions>
#include <QVector3D>
#include "cube.h"

class Sphere : protected QOpenGLFunctions
{
public:
    Sphere(QVector3D pos, float radius, float kg);
    Sphere();
    ~Sphere();

    void draw();
    void fadeToColor(float redFade, float greenFade, float blueFade);

    //Setter
    void setColor(float red, float green, float blue);
    void setPos(QVector3D pod);
    void setDirection(QVector3D direction);
    void setRadius(float radius);
    void setMass(float mass);

    //Getter
    QVector3D getPos();
    QVector3D getDirection();
    float getRadius();
    float getMass();
    float getArea();

private:
    //Sphere
    QVector3D pos;
    QVector3D direction;
    float radius;
    float kg;

    //Color
    float red;
    float green;
    float blue;
    float redFade;
    float greenFade;
    float blueFade;
};

#endif // SPHERE_H

#ifndef SPHERE_H
#define SPHERE_H

#include <QOpenGLFunctions>
#include <QVector3D>
#include "cube.h"

class Sphere : protected QOpenGLFunctions
{
public:
    Sphere(QVector3D pos, float radius);
    Sphere();
    ~Sphere();

    void draw();
    bool checkIntersection(Cube &cube, float &lamda);

    //Setter
    void setColor(float red, float green, float blue);
    void setPos(QVector3D pod);
    void setDirection(QVector3D direction);
    void updatePosition();
    void setRadius(float radius);

    //Getter
    QVector3D getPos();
    QVector3D getDirection();
    float getRadius();

private:
    //Sphere
    QVector3D pos;
    QVector3D direction;
    float radius;

    //Color
    float red;
    float green;
    float blue;
};

#endif // SPHERE_H

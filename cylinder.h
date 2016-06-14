#ifndef CYLINDER_H
#define CYLINDER_H

#include <QOpenGLFunctions>
#include <QVector3D>
#include <cmath>

class Cylinder
{
public:
    Cylinder(QVector3D pos, float radius, float height);
    ~Cylinder();

    void draw();
    void setColor(float red, float green, float blue);
    void setPos(QVector3D pos);
    void setHeight(float height);
    void setRadius(float radius);

private:
    //Cylinder
    QVector3D pos;
    float radius;
    float height;

    int strips; //wie viele "ecken" soll der zylinder haben

    //color
    float red;
    float green;
    float blue;

};

#endif // CYLINDER_H

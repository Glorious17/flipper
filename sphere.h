#ifndef SPHERE_H
#define SPHERE_H

#include <QOpenGLFunctions>
#include <QVector3D>

class Sphere
{
public:
    Sphere(QVector3D pos, float radius);
    ~Sphere();

    void draw();

    //Setter
    void setColor(float red, float green, float blue);
    void setPos(QVector3D);
    void setRadius(float radius);

    //Getter
    QVector3D getPos();
    float getRadius();

private:
    //Sphere
    QVector3D pos;
    float radius;

    //Color
    float red;
    float green;
    float blue;
};

#endif // SPHERE_H

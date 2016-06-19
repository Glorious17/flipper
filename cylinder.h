#ifndef CYLINDER_H
#define CYLINDER_H

#include <QOpenGLFunctions>
#include <QVector3D>

class Cylinder : protected QOpenGLFunctions
{
public:
    Cylinder(QVector3D pos, float radius, float height);
    Cylinder();
    ~Cylinder();

    void draw();

    //Setter
    void setColor(float red, float green, float blue);
    void setPos(QVector3D pos);
    void setHeight(float height);
    void setRadius(float radius);

    //Getter
    QVector3D getPos();
    float getHeight();
    float getRadius();

private:
    //Cylinder
    QVector3D pos;
    float radius;
    float height;

    //color
    float red;
    float green;
    float blue;

};

#endif // CYLINDER_H

#ifndef PLANE_H
#define PLANE_H

#include <QVector3D>

class Plane
{
public:
    Plane(QVector3D pos, QVector3D normal, float length);
    Plane();
    ~Plane();

    void setPos(QVector3D pos);
    void setNormal(QVector3D normal);

    QVector3D getPos();
    QVector3D getNormal();
    float getLength();

private:
    QVector3D pos;
    QVector3D normal;
    float length;
};

#endif // PLANE_H

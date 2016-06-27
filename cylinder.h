#ifndef CYLINDER_H
#define CYLINDER_H

#include <QOpenGLFunctions>
#include <QVector3D>
#include <QMatrix4x4>

class Cylinder : protected QOpenGLFunctions
{
public:
    Cylinder(QVector3D pos, float radius, float height);
    Cylinder();
    ~Cylinder();

    void draw();
    QVector3D getGlobalCoordinatesOfPoint(QVector3D local);
    QVector3D getGlobalCoordinatesOfVector(QVector3D local);
    void fadeToColor(float redFade, float greenFade, float blueFade);

    //Setter
    void setColor(float red, float green, float blue);
    void setPos(QVector3D pos);
    void setRotation(float xRot, float yRot, float zRot);

    //Getter
    QVector3D getPos();
    float getHeight();
    float getRadius();

private:
    //Cylinder
    QVector3D pos;
    QVector3D axis;
    float xRot;
    float yRot;
    float zRot;
    float radius;
    float height;

    QMatrix4x4 rotMatrix;
    QMatrix4x4 tranMatrix;

    //color
    float red;
    float green;
    float blue;

    float redFade;
    float greenFade;
    float blueFade;
};

#endif // CYLINDER_H

#ifndef CUBE_H
#define CUBE_H

#include <QOpenGLFunctions>
#include <QVector3D>
#include <QMatrix4x4>
#include "sphere.h"

class Cube : protected QOpenGLFunctions
{
public:
    Cube(QVector3D pos, float width, float height, float length);
    Cube();
    ~Cube();

    void draw();
    QVector3D getGlobalCoordinatesOfPoint(QVector3D local);
    QVector3D getGlobalCoordinatesOfVector(QVector3D local);
    boolean checkIntersectionSphere(Sphere sphere, float &lamda);

    //Setter
    void setColor(float red, float green, float blue);
    void setPos(QVector3D pos);
    void setWidth(float width);
    void setHeight(float height);
    void setLength(float length);
    void setRotation(float xRot, float yRot, float zRot);

    //Getter
    QVector3D getPos();
    float getWidth();
    float getHeight();
    float getLength();
    float getXRot();
    float getZRot();

private:
    //Cube
    QVector3D pos;
    float width;
    float height;
    float length;
    float xRot;
    float yRot;
    float zRot;

    QMatrix4x4 rotMatrix;
    QMatrix4x4 tranMatrix;

    //Color
    float red;
    float green;
    float blue;


};

#endif // CUBE_H

#ifndef CUBE_H
#define CUBE_H

#include <QOpenGLFunctions>
#include <QVector3D>
#include <QMatrix4x4>
#include "plane.h"

class Cube : protected QOpenGLFunctions
{
public:
    Cube(QVector3D pos, float width, float height, float length);
    Cube();
    ~Cube();

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
    float getWidth();
    float getHeight();
    float getLength();
    float getXRot();
    float getZRot();
    Plane getTopPlane();
    Plane getBottomPlane();
    Plane getRightPlane();
    Plane getLeftPlane();
    QVector3D getMin();
    QVector3D getMax();
    QVector3D getTop();
    QVector3D getBottom();
    QVector3D getRight();
    QVector3D getLeft();
    QVector3D getFront();
    QVector3D getBack();

private:
    //Cube
    QVector3D pos;
    float width;
    float height;
    float length;
    float xRot;
    float yRot;
    float zRot;

    QVector3D plane_top;
    QVector3D plane_bottom;
    QVector3D plane_right;
    QVector3D plane_left;
    QVector3D plane_front;
    QVector3D plane_back;

    QMatrix4x4 rotMatrix;
    QMatrix4x4 tranMatrix;

    //Color
    float red;
    float green;
    float blue;

    float redFade;
    float greenFade;
    float blueFade;
};

#endif // CUBE_H

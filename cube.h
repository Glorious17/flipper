#ifndef CUBE_H
#define CUBE_H

#include <QOpenGLFunctions>
#include <QVector3D>

class Cube
{
public:
    Cube(QVector3D pos, float width, float height, float length);
    ~Cube();

    void draw();
    void setColor(float red, float green, float blue);
    void setPos(QVector3D pos);
    void setWidth(float width);
    void setHeight(float height);
    void setLength(float length);

private:
    //Cube
    QVector3D pos;
    float width;
    float height;
    float length;

    //Color
    float red;
    float green;
    float blue;


};

#endif // CUBE_H

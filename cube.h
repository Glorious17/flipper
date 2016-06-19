#ifndef CUBE_H
#define CUBE_H

#include <QOpenGLFunctions>
#include <QVector3D>

class Cube : protected QOpenGLFunctions
{
public:
    Cube(QVector3D pos, float width, float height, float length);
    Cube();
    ~Cube();

    void draw();

    //Setter
    void setColor(float red, float green, float blue);
    void setPos(QVector3D pos);
    void setWidth(float width);
    void setHeight(float height);
    void setLength(float length);

    //Getter
    QVector3D getPos();
    float getWidth();
    float getHeight();
    float getLength();

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

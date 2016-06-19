#ifndef GEOOBJECT_H
#define GEOOBJECT_H

#include <QOpenGLFunctions>
#include <QVector3D>

class GeoObject : protected QOpenGLFunctions
{
public:
    GeoObject();
    ~GeoObject();

    void draw();

    //Setter
    void setColor(float red, float green, float blue);
    void setPos(QVector3D pos);

    //Getter
    QVector3D getPos();

private:
    //Objekt Eigenschaften
    QVector3D pos;

    //Farbe
    float red;
    float green;
    float blue;
};

#endif // GEOOBJECT_H

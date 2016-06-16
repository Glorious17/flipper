#include "sphere.h"
#include <cmath>

Sphere::Sphere(QVector3D pos, float radius)
{
    this->pos = pos;
    this->radius = radius;

    red = 1.0;
    green = 1.0;
    blue = 1.0;
}

Sphere::~Sphere()
{
}

void Sphere::draw(){


    int latitudes = 45;         //breitengrade = horizontal
    int longtitudes = 45;       //längengrade = vertikal

    //https://de.wikipedia.org/wiki/Kugel

    float hor_delta = (2.0f * M_PI)/hor_strips;
    float ver_delta = (M_PI)/ver_strips;


    for(int i = 0; i < ver_strips; i++){

        float ver_step = i * ver_delta;

        glBegin(GL_QUAD_STRIP);
        glColor3f(red, green, blue);
        for(int j = 0; j < hor_strips; j++){
            float hor_step = j * hor_delta;

            float xn = sinf(ver_step) * sinf(hor_step);
            float yn = sinf(ver_step) * cosf(hor_step);
            float zn = sinf(ver_step) * cosf(hor_step);

            float x = pos.x() + radius * xn;
            float y = pos.y() + radius * yn;
            float z = pos.z() + radius * zn;

            glNormal3f(xn, yn, zn);
            glVertex3f(x, y, z);

            xn = sinf(ver_step) * sinf(hor_step + hor_delta);
            yn = sinf(ver_step) * cosf(hor_step + hor_delta);
            zn = sinf(ver_step) * cosf(hor_step + hor_delta);

            x = pos.x() + radius * xn;
            y = pos.y() + radius * yn;
            z = pos.z() + radius * zn;

            glVertex3f(x, y, z);
        }
        glEnd();
    }

    /*int nr_lat = 45;
    int nr_lon = 45;

    // Angle delta in both directions
    const float lat_delta = M_PI / float( nr_lat );
    const float lon_delta = M_PI / float( nr_lon );

    // Create horizontal stripes of squares
    for( float lon = 0.0f; lon < 1.0f*M_PI; lon += lon_delta )
    {
        glBegin( GL_QUAD_STRIP ) ;
        glColor3f(red, green, blue);
        for( float lat = 0.0f; lat <= 2.0f*M_PI; lat += lat_delta )
        {
            // Each iteration adds another square, the other vertices
            // are taken from the existing stripe
            float xn1 = cosf( lat ) * sinf( lon );
            float yn1 = sinf( lat ) * sinf( lon );
            float zn1 = cosf( lon );

            // Set normal vector (important for lighting!)
            glNormal3f( xn1, yn1, zn1 );
            glVertex3f( pos.x()+radius*xn1, pos.y()+radius*yn1, pos.z()+radius*zn1 );

            float xn2 = cosf( lat ) * sinf( lon + lon_delta );
            float yn2 = sinf( lat ) * sinf( lon + lon_delta );
            float zn2 = cosf( lon + lon_delta );

            glNormal3f( xn2, yn2, zn2 );
            glVertex3f( pos.x()+radius*xn2, pos.y()+radius*yn2, pos.z()+radius*zn2 );
        }
        glEnd() ;
    }*/
}

//Setter---------------------------------------------------

void Sphere::setColor(float red, float green, float blue){
    this->red = red;
    this->green = green;
    this->blue = blue;
}

void Sphere::setPos(QVector3D pos){
    this->pos = pos;
}

void Sphere::setRadius(float radius){
    this->radius = radius;
}


//Getter---------------------------------------------------

QVector3D Sphere::getPos(){
    return pos;
}

float Sphere::getRadius(){
    return radius;
}






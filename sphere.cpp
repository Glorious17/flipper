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

Sphere::Sphere(){

}

Sphere::~Sphere()
{
}

void Sphere::draw(){


    int latitudes = 90;         //breitengrade = horizontal
    int longtitudes = 90;       //längengrade = vertikal

    //https://de.wikipedia.org/wiki/Kugel

    float hor_delta = (2.0f * M_PI)/float(latitudes);  //delta_theta
    float ver_delta = (M_PI)/float(longtitudes);       //delta_phi

    glColor3f(red, green, blue);
    for(float i = 0.0; i < 1.0f * M_PI; i += ver_delta){
        glBegin(GL_QUAD_STRIP);
        for(float j = 0.0; j <= 2.0f*M_PI + hor_delta; j += hor_delta){

            float xn = sinf(i) * cosf(j);
            float yn = sinf(i) * sinf(j);
            float zn = cosf(i);

            glNormal3f(xn, yn, zn);
            glVertex3f(pos.x() + radius * xn, pos.y() + radius * yn, pos.z() + radius * zn);

            float xn2 = sinf(i+ver_delta) * cosf(j);
            float yn2 = sinf(i+ver_delta) * sinf(j);
            float zn2 = cosf(i+ver_delta);

            glVertex3f(pos.x() + radius * xn2, pos.y() + radius * yn2, pos.z() + radius * zn2);
        }
        glEnd();
    }

    /*
    // Angle delta in both directions
    const float lat_delta = M_PI / float( 90 );
    const float lon_delta = M_PI / float( 90 );

    // Create horizontal stripes of squares
    for( float lon = 0.0f; lon < 1.0f*M_PI; lon += lon_delta )
    {
        glBegin( GL_QUAD_STRIP ) ;
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






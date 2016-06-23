#include "cube.h"

Cube::Cube(QVector3D pos, float width, float height, float length)
{
    this->pos = pos;
    this->width = width;
    this->height = height;
    this->length = length;
    xRot = 0.0;
    yRot = 0.0;
    zRot = 0.0;

    rotMatrix = QMatrix4x4();
    tranMatrix = QMatrix4x4();
    tranMatrix.translate(pos);

    red = 1.0;
    green = 1.0;
    blue = 1.0;
}

Cube::Cube(){

}

Cube::~Cube(){
}

void Cube::draw(){

    glPushMatrix();

    glTranslatef(pos.x(), pos.y(), pos.z());

    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);
    glRotatef(zRot, 0.0, 0.0, 1.0);

    //Punkt rechts unten vorne
    float x = (width/2.0);
    float y = -(height/2.0);
    float z = (length/2.0);

    //Alle Eckpunkte werden für alle Seiten in den Array geschrieben
    float faces[6][4][3] = {
        {{x, y, z}, {x, y+height, z}, {x-width, y+height, z}, {x-width, y, z}}, //FRONT
        {{x, y, z-length}, {x, y+height, z-length}, {x-width, y+height, z-length}, {x-width, y, z-length}}, //BACK
        {{x, y, z}, {x, y, z-length}, {x, y+height, z-length}, {x, y+height, z}}, // RIGHT
        {{x-width, y, z}, {x-width, y+height, z}, {x-width, y+height, z-length}, {x-width, y, z-length}}, // LEFT
        {{x, y+height, z}, {x, y+height, z-length}, {x-width, y+height, z-length}, {x-width, y+height, z}}, //TOP
        {{x, y, z}, {x, y, z-length}, {x-width, y, z-length}, {x-width, y, z}} // BOTTOM
    };

    /*
    //Wenn jede seite des Cubes eine andere Farbe haben soll
    float colors[6][3] = {
        {0.6, 0.6, 0.6}, //FRONT
        {1.0, 0.0, 0.0}, //BACK
        {0.0, 0.0, 1.0}, //RIGHT
        {0.0, 1.0, 0.0}, //LEFT
        {0.0, 1.0, 1.0}, //TOP
        {1.0, 1.0, 1.0} //BOTTOM
    };*/

    //Setzt für jede Seite einen Normalvektor
    float normals[6][3] = {
        {0.0, 0.0, 1.0}, //FRONT
        {0.0, 0.0, -1.0}, //BACK
        {1.0, 0.0, 0.0}, //RIGHT
        {-1.0, 0.0, 0.0}, //LEFT
        {0.0, 1.0, 0.0}, //TOP
        {0.0, -1.0, 0.0} //BOTTOM
    };

    //erstellt alle 6 seiten eines Quaders
    glColor3f(red, green, blue);
    glBegin(GL_QUADS);
        for(int i = 0; i < 6; i++){
            glNormal3f(normals[i][0], normals[i][1], normals[i][2]);
            glVertex3f(faces[i][0][0], faces[i][0][1], faces[i][0][2]);
            glVertex3f(faces[i][1][0], faces[i][1][1], faces[i][1][2]);
            glVertex3f(faces[i][2][0], faces[i][2][1], faces[i][2][2]);
            glVertex3f(faces[i][3][0], faces[i][3][1], faces[i][3][2]);
        }
    glEnd();

    glBegin(GL_LINES);
        glVertex3f(0.0, height/2.0, 0.0);
        glVertex3f(normals[4][0], (height/2.0) + normals[4][1], normals[4][2]);
    glEnd();

    glPopMatrix();
}

boolean Cube::checkIntersectionSphere(Sphere sphere, float& lamda){

    QVector3D spherePos = sphere.getPos();

    /*//checking bounding box

    QVector3D linksUnten = getGlobalCoordinatesOfPoint(QVector3D(-width/2.0, -height/2.0, 0.0));
    QVector3D linksOben = getGlobalCoordinatesOfPoint(QVector3D(-width/2.0, height/2.0, 0.0));
    QVector3D rechtsUnten = getGlobalCoordinatesOfPoint(QVector3D(width/2.0, -height/2.0, 0.0));
    QVector3D rechtsOben = getGlobalCoordinatesOfPoint(QVector3D(width/2.0, height/2.0, 0.0));

    if((spherePos.x() > rechtsOben.x() && spherePos.x() > rechtsUnten.x()) ||
            (spherePos.x() < linksOben.x() && spherePos.x() < linksUnten.x()) ||
            (spherePos.y() > linksOben.y() && spherePos.y() > rechtsOben.y()) ||
            (spherePos.y() < linksUnten.y() && spherePos.y() < rechtsUnten.y())){
        return false;
    }

    qDebug("is in");*/

    //TOP PLANE

    QVector3D x = getGlobalCoordinatesOfPoint(QVector3D(0.0, height/2.0, 0.0));
    QVector3D xn = getGlobalCoordinatesOfVector(QVector3D(0.0, 1.0, 0.0));

    float skalarProdukt = QVector3D::dotProduct(sphere.getDirection(), xn);

    if(skalarProdukt == 0.0){               //Wenn das Skalaprodukt 0 ist, sind die Vektoren senkrecht zueinander
        return false;
    }

    lamda = (QVector3D::dotProduct(xn, x - spherePos)/skalarProdukt);

    if(lamda < 0){
        return false;
    }
    return true;
}

QVector3D Cube::getGlobalCoordinatesOfPoint(QVector3D local){
    QMatrix4x4 matrix = tranMatrix * rotMatrix;
    QVector3D global = matrix * (local);
    return global;
}

QVector3D Cube::getGlobalCoordinatesOfVector(QVector3D local){
    QVector3D global = rotMatrix * (local);
    return global;
}

//Setter---------------------------------------------------

void Cube::setColor(float red, float green, float blue){
    this->red = red;
    this->green = green;
    this->blue = blue;
}

void Cube::setPos(QVector3D pos){
    QVector3D dPos = QVector3D(pos.x() - this->pos.x(), pos.y() - this->pos.y(), pos.z() - this->pos.z());
    tranMatrix.translate(dPos);

    this->pos = pos;
}

void Cube::setWidth(float width){
    this->width = width;
}

void Cube::setHeight(float height){
    this->height = height;
}

void Cube::setLength(float length){
    this->length = length;
}

void Cube::setRotation(float xRot, float yRot, float zRot){
    float dxRot = xRot - this->xRot;
    float dyRot = yRot - this->yRot;
    float dzRot = zRot - this->zRot;
    rotMatrix.rotate(dxRot, 1.0, 0.0, 0.0);
    rotMatrix.rotate(dyRot, 0.0, 1.0, 0.0);
    rotMatrix.rotate(dzRot, 0.0, 0.0, 1.0);

    this->xRot = xRot;
    this->yRot = yRot;
    this->zRot = zRot;

}

//Getter---------------------------------------------------

QVector3D Cube::getPos(){
    return pos;
}

float Cube::getWidth(){
    return width;
}

float Cube::getHeight(){
    return height;
}

float Cube::getLength(){
    return length;
}

float Cube::getXRot(){
    return xRot;
}

float Cube::getZRot(){
    return zRot;
}










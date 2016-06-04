#include "myopenglwidget.h"

myOpenGLWidget::myOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    xRot = 0;
    yRot = 0;
    zRot = 0;
}

myOpenGLWidget::~myOpenGLWidget()
{
}

void myOpenGLWidget::initializeGL(){
    initializeOpenGLFunctions();

    // Use depth testing and the depth buffer
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Calculate color for each pixel fragment
    glShadeModel(GL_SMOOTH);

    // Enable lighting in scene
    glEnable(GL_LIGHTING);

    // Set position of light source
    float light_pos[] = { 10.f, 5.f, 10.f, 0.f };
    glLightfv(GL_LIGHT1, GL_POSITION, light_pos );

    // Set color for this light source
    // (We are only specifying a diffuse light source)
    float light_diffuse[] = { .8f, .8f, .8f, 1.f };
    glLightfv(GL_LIGHT1, GL_DIFFUSE,  light_diffuse );

    // Turn on this light
    glEnable(GL_LIGHT1);

    // Use the color of an object for light calculation
    glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
    glEnable(GL_COLOR_MATERIAL);
}

void myOpenGLWidget::paintGL(){
    // Clear the scene
    glClearColor(0.f, 0.f, 0.f, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Apply rotation angles
    glRotatef(xRot, 1.0f, 0.0f, 0.0f); // Rotate around x axis
    glRotatef(yRot, 0.0f, 1.0f, 0.0f); // Rotate around y axis
    glRotatef(zRot, 0.0f, 0.0f, 1.0f); // Rotate around z axis

    // --> Now, every position is multiplied by the rotation matrix
    //     and by the scaling matrix

    // Draw a trinagle

    glColor3f( 0.0f, 1.0f, 0.0f );

    glBegin(GL_TRIANGLES);
     glNormal3f( 0.0,  0.0, 1.0);
     glVertex3f( 0.0,  2.0, 0.0);
     glVertex3f(-2.0, -2.0, 0.0);
     glVertex3f( 2.0, -2.0, 0.0);
    glEnd();
}

void myOpenGLWidget::resizeGL(int width, int height){
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void myOpenGLWidget::setXRotation(int angle){

}

void myOpenGLWidget::setYRotation(int angle){

}

void myOpenGLWidget::setZRotation(int angle){

}


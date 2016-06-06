#include "qoglwidget.h"

QOGLWidget::QOGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    xRot = 0;
    yRot = 0;
    zRot = 0;
}

QOGLWidget::~QOGLWidget()
{

}


void QOGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0,1,1,1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
}

void QOGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void QOGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //rechts/links | oben/unten | vorne/hinten
    glTranslatef(0.0, 0.0, 0.0);


    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);
    glRotatef(zRot, 0.0, 0.0, 1.0);

    glBegin(GL_TRIANGLES);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(-0.5, -0.5, 0);
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(0.5, -0.5, 0);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0.0, 0.5, 0);
    glEnd();
}

void QOGLWidget::mousePressEvent(QMouseEvent *event)
{
    lastpos = event->pos();
}

void QOGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    // ... and while moving, we calculate the dragging deltas

    // Left button: Rotating around y axis

    if(event->buttons() == Qt::LeftButton)
    {
        int dx = 0;
        int dy = 0;
        int dz = 0;
        dy = lastpos.x() - event->x();

        // Now let the world know that we want to rotate
        emit changeRotation( dx, dy, dz );
    }

    // Right button: Rotating around z and y axis
    //int dy = (event->buttons() & Qt::LeftButton) ? lastpos.x() - event->x() : 0;

    if(event->buttons() == Qt::RightButton)
    {
        int dx = 0;
        int dy = 0;
        dx = lastpos.x() - event->x();
        dy = lastpos.y() - event->y();

        // Now let the world know that we want to rotate
        emit changeTranslation( dx, dy );
    }

    // Make the current position the starting point for the next dragging step
    lastpos = event->pos();
}

void QOGLWidget::setXRotation(int angle)
{
    xRot = angle;
    emit xRotationChanged(angle);
    update();
}

void QOGLWidget::setYRotation(int angle)
{
    yRot = angle;
    emit yRotationChanged(angle);
    update();
}

void QOGLWidget::setZRotation(int angle)
{
    zRot = angle;
    emit zRotationChanged(angle);
    update();
}









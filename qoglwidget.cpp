#include "qoglwidget.h"

QOGLWidget::QOGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    xRot = -25.0;
    yRot = 25.0;
    zRot = 0;

    xTran = 0;
    yTran = 0;
}

QOGLWidget::~QOGLWidget()
{

}


void QOGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0,0,0,1);
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
    glTranslatef(xTran, yTran, 0.0);

    //rotate
    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);
    glRotatef(zRot, 0.0, 0.0, 1.0);

    drawQuad(0.0, 0.0, 0.0, 1.5, 0.5, 0.1);
}

void QOGLWidget::drawQuad(float mx, float my, float mz, float width, float height, float length)
{
    float hWidth = width/2.0;
    float hHeight = height/2.0;
    float hLength = length/2.0;

    glColor3f(1.0, 0.0, 0.0);

    glBegin(GL_QUADS);
        glVertex3f(mx - hWidth, my - hHeight, mz - hLength);
        glVertex3f(mx - hWidth, my + hHeight, mz - hLength);
        glVertex3f(mx + hWidth, my + hHeight, mz - hLength);
        glVertex3f(mx + hWidth, my - hHeight, mz - hLength);
    glEnd();

    glColor3f(0.0, 1.0, 0.0);

    glBegin(GL_QUADS);
        glVertex3f(mx + hWidth, my + hHeight, mz - hLength);
        glVertex3f(mx + hWidth, my + hHeight, mz + hLength);
        glVertex3f(mx + hWidth, my - hHeight, mz + hLength);
        glVertex3f(mx + hWidth, my - hHeight, mz - hLength);
    glEnd();

    glColor3f(0.0, 0.0, 1.0);

    glBegin(GL_QUADS);
        glVertex3f(mx - hWidth, my - hHeight, mz + hLength);
        glVertex3f(mx - hWidth, my + hHeight, mz + hLength);
        glVertex3f(mx + hWidth, my + hHeight, mz + hLength);
        glVertex3f(mx + hWidth, my - hHeight, mz + hLength);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_QUADS);
        glVertex3f(mx - hWidth, my + hHeight, mz - hLength);
        glVertex3f(mx - hWidth, my + hHeight, mz + hLength);
        glVertex3f(mx - hWidth, my - hHeight, mz + hLength);
        glVertex3f(mx - hWidth, my - hHeight, mz - hLength);
    glEnd();

    glColor3f(0.0, 1.0, 1.0);

    glBegin(GL_QUADS);
        glVertex3f(mx - hWidth, my + hHeight, mz - hLength);
        glVertex3f(mx - hWidth, my + hHeight, mz + hLength);
        glVertex3f(mx + hWidth, my + hHeight, mz + hLength);
        glVertex3f(mx + hWidth, my + hHeight, mz - hLength);
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

    // Right button: Translating to left/right, up/down
    if(event->buttons() == Qt::RightButton)
    {
        float dx = 0;
        float dy = 0;
        dx = ((lastpos.x() - event->x()) * 0.01);
        dy = ((lastpos.y() - event->y()) * 0.01) * (-1);

        // Now let the world know that we want to translate
        emit changeTranslation( dx, dy );
    }

    // Make the current position the starting point for the next dragging step
    lastpos = event->pos();
}

void QOGLWidget::onChangeTranslation(float dx, float dy)
{
    // To apply the requested Translation deltas, we increment...
    xTran = xTran + dx;
    yTran = yTran + dy;

    update();
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









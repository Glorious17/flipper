#ifndef QOGLWIDGET_H
#define QOGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QVector3D>
#include <QWheelEvent>
#include <QTimer>
#include "cube.h"
#include "cylinder.h"
#include "sphere.h"

class QOGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    QOGLWidget(QWidget *parent = 0);
    ~QOGLWidget();

private:

    QPoint lastpos;
    QTimer* timer_game;

    float xRot;
    float yRot;

    float xTran;
    float yTran;
    float zTran;

    float scale;

    const static int nr_cubes = 4;

    Cube cube[nr_cubes];
    Sphere ball;

    void checkCollision(Sphere &sphere, Cube cube);
    void changeZoom(float dzoom);
    void changeRotation(float dx, float dy);
    void changeTranslation(float dx, float dy);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

public slots:
    void gameUpdate();
};

#endif // QOGLWIDGET_H

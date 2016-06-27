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
#include "plane.h"

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

    static const int NR_CUBES = 5;
    static constexpr float GRAVITY = 0.00981f;
    static constexpr float REIBUNGSKONSTANTE = 0.1;

    Cube cube[NR_CUBES];
    Cube obstacle;
    Sphere ball;
    Cylinder goal;

    bool checkCollision(Cube &cube, Sphere &sphere, QVector3D &collision_point, QVector3D &collision_normal, float &lambda);
    bool checkIntersection(QVector3D planePos, QVector3D planeNormal, QVector3D spherePos, QVector3D sphereDirection, float &lambda);
    bool checkIntersection(Cylinder cylinder, QVector3D spherePos, QVector3D sphereDirection, float radius, float &lambda);
    bool isPointInCubePlane(QVector3D point, Plane &plane);
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

#ifndef QOGLWIDGET_H
#define QOGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMouseEvent>
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

    int xRot;
    int yRot;
    int zRot;
    float xTran;
    float yTran;
    float scale;

    float height;

    Cube cube1 = Cube(QVector3D(0.0, 0.0, 0.0), 1.0, 0.5, 2.0);
    Cylinder cylinder1 = Cylinder(QVector3D(-4.0, 1.0, 0.0), 2, 2);
    Sphere sphere1 = Sphere(QVector3D(0.0, 1.35, 0.0), 0.15);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

public slots:
    void onChangeZoom(float dzoom);
    void onChangeRotation(int dx, int dy, int dz);
    void onChangeTranslation(float dx, float dy);
    void gameUpdate();

signals:
    void changeZoom(float dzoom);
    void changeRotation(int dx, int dy, int dz);
    void changeTranslation(float dx, float dy);
};

#endif // QOGLWIDGET_H

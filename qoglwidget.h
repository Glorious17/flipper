#ifndef QOGLWIDGET_H
#define QOGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMouseEvent>
#include <QVector3D>
#include <QWheelEvent>
#include "cube.h"
#include "cylinder.h"

class QOGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    QOGLWidget(QWidget *parent = 0);
    ~QOGLWidget();

private:
    QPoint lastpos;
    int xRot;
    int yRot;
    int zRot;
    float xTran;
    float yTran;
    float scale;
    Cube cube1 = Cube(QVector3D(0.0, 0.0, 0.0), 1.0, 0.5, 2.0);
    Cylinder cylinder1 = Cylinder(QVector3D(0.0, 0.0, 0.0), 2, 4);
    void drawSphere(QVector3D pos, float rad = 1.f, int nr_lat = 90, int nr_lon = 90 );

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

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);
    void changeZoom(float dzoom);
    void changeRotation(int dx, int dy, int dz);
    void changeTranslation(float dx, float dy);
};

#endif // QOGLWIDGET_H

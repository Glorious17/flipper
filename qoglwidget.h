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

    int xRot;
    int yRot;
    int zRot;
    float xTran;
    float yTran;
    float zTran;
    float scale;

    const static int nr_cubes = 4;

    Cube cube[nr_cubes];
    Sphere ball;

    void checkCollision(Sphere sphere, Cube cube);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

public slots:
    void onChangeZoom(float dzoom);
    void onChangeRotation(int dx, int dy, int dz);
    void onChangeTranslation(float dx, float dy, float dz);
    void gameUpdate();

signals:
    void changeZoom(float dzoom);
    void changeRotation(int dx, int dy, int dz);
    void changeTranslation(float dx, float dy, float dz);
};

#endif // QOGLWIDGET_H

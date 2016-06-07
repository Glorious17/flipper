#ifndef QOGLWIDGET_H
#define QOGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMouseEvent>
#include <QVector3D>
#include <QWheelEvent>

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

    void drawQuad(float mx, float my, float mz, float width, float height, float length);
    void drawSphere(const QVector3D &pos, float rad = 1.f, int nr_lat = 90, int nr_lon = 90 );

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void onChangeZoom(float dzoom);
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

#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMouseEvent>
#include <QVector3D>

class myOpenGLWidget : public QOpenGLWidget,
                       protected QOpenGLFunctions
{
    Q_OBJECT

public:
    myOpenGLWidget(QWidget *parent = 0);
    ~myOpenGLWidget();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

private:
    int xRot;
    int yRot;
    int zRot;

/*signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);*/

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
};

#endif // MYOPENGLWIDGET_H

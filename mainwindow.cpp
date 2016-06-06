#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->xRotSlider, SIGNAL(valueChanged(int)), ui->openGLWidget, SLOT(setXRotation(int)));
    connect(ui->yRotSlider, SIGNAL(valueChanged(int)), ui->openGLWidget, SLOT(setYRotation(int)));
    connect(ui->zRotSlider, SIGNAL(valueChanged(int)), ui->openGLWidget, SLOT(setZRotation(int)));

    connect(ui->openGLWidget, SIGNAL(changeRotation(int, int, int)), this, SLOT(onChangeRotation(int, int, int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onChangeRotation(int dx, int dy, int dz)
{
    // To apply the requested rotation deltas, we increment...
    int newx = ui->xRotSlider->value() + dx;
    int newy = ui->yRotSlider->value() + dy;
    int newz = ui->zRotSlider->value() + dz;

    // ... and set the sliders to the new angles mod 360 (to ensure 0..359)
    ui->xRotSlider->setValue( newx % 360 );
    ui->yRotSlider->setValue( newy % 360 );
    ui->zRotSlider->setValue( newz % 360 );

    // NB: SetValue will emit valueChanged signal, so the scene gets updated
}

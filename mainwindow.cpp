#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->xRotSlider, SIGNAL(valueChanged(int)), ui->openGLWidget, SLOT(setXRotation(int angle)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

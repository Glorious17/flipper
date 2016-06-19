#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->openGLWidget, SIGNAL(changeRotation(int, int, int)), ui->openGLWidget, SLOT(onChangeRotation(int, int, int)));
    connect(ui->openGLWidget, SIGNAL(changeTranslation(float, float, float)), ui->openGLWidget, SLOT(onChangeTranslation(float, float, float)));
    connect(ui->openGLWidget, SIGNAL(changeZoom(float)), ui->openGLWidget, SLOT(onChangeZoom(float)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

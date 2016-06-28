#-------------------------------------------------
#
# Project created by QtCreator 2016-06-02T11:39:57
#
#-------------------------------------------------

QT       += core gui opengl

LIBS    += -lOpengl32

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PUZZLE 3D
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qoglwidget.cpp \
    cube.cpp \
    cylinder.cpp \
    sphere.cpp \
    plane.cpp

HEADERS  += mainwindow.h \
    qoglwidget.h \
    cube.h \
    cylinder.h \
    sphere.h \
    plane.h

FORMS    += mainwindow.ui

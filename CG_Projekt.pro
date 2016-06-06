#-------------------------------------------------
#
# Project created by QtCreator 2016-06-02T11:39:57
#
#-------------------------------------------------

QT       += core gui opengl

LIBS    += -lOpengl32

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CG_Projekt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qoglwidget.cpp

HEADERS  += mainwindow.h \
    qoglwidget.h

FORMS    += mainwindow.ui

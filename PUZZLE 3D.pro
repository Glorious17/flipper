#-------------------------------------------------
#
# Project created by QtCreator 2016-06-02T11:39:57
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 5): QT += openglwidgets

win32: LIBS += -lopengl32

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Puzzle3D
TEMPLATE = app

INCLUDEPATH += src

SOURCES += src/main.cpp \
    src/mainwindow.cpp \
    src/qoglwidget.cpp \
    src/cube.cpp \
    src/cylinder.cpp \
    src/sphere.cpp \
    src/plane.cpp

HEADERS += src/mainwindow.h \
    src/qoglwidget.h \
    src/cube.h \
    src/cylinder.h \
    src/sphere.h \
    src/plane.h \
    src/legacyopenglfunctions.h

FORMS += ui/mainwindow.ui

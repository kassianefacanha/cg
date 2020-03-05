#-------------------------------------------------
#
# Project created by QtCreator 2018-03-02T09:29:27
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtOpenGLdoZero20181
TEMPLATE = app

CONFIG += c++11

LIBS += -lGLU

INCLUDEPATH += bib

SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    bib/Camera.cpp \
    bib/CameraDistante.cpp \
    bib/CameraJogo.cpp \
    bib/Desenha.cpp \
    bib/Vetor3D.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    bib/Camera.h \
    bib/CameraDistante.h \
    bib/CameraJogo.h \
    bib/Desenha.h \
    bib/Vetor3D.h

FORMS    += mainwindow.ui

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lGL -lGLU -lglut

#INCLUDE_PATH += bib

SOURCES += main.cpp \
    bib/Camera.cpp \
    bib/CameraDistante.cpp \
    bib/CameraJogo.cpp \
    bib/Desenha.cpp \
    bib/Vetor3D.cpp

HEADERS += \
    bib/Camera.h \
    bib/CameraDistante.h \
    bib/CameraJogo.h \
    bib/Desenha.h \
    bib/Vetor3D.h


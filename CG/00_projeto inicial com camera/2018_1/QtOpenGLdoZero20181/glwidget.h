#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QtOpenGL>

#include <bib/Desenha.h>
#include <CameraDistante.h>

class GLWidget : public QGLWidget
{
    Q_OBJECT
private:
    float width = 800;
    float height = 600;

    float trans_obj = false;

    float tx = 0.0;
    float ty = 0.0;
    float tz = 0.0;

    float ax = 0.0;
    float ay = 0.0;
    float az = 0.0;

    //float delta = 5.0;

    float sx = 1.0;
    float sy = 1.0;
    float sz = 1.0;

    float slices = 20;
    float stacks = 20;

    float z = 0.0;
    float r = 0.0;
    float g = 0.0;
    float b = 0.0;

    bool lbpressed = false;
    bool mbpressed = false;
    bool rbpressed = false;

    float last_x = 0.0;
    float last_y = 0.0;

    Camera* cam = new CameraDistante();
    float savedCamera[9];

    QTimer timer;
    QPoint lastPos;
public:
    explicit GLWidget(QWidget *parent = 0);

    void initializeGL();
    void paintGL();
        void displayInit();
        void displayEnd();
    void resizeGL(int w, int h);

    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

signals:

public slots:
};

#endif // GLWIDGET_H

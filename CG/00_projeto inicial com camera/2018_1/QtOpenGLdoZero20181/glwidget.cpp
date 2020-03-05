#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
{
    connect( &timer, SIGNAL(timeout()), this, SLOT(updateGL()) );
    timer.start(16);
}

void GLWidget::initializeGL()
{
    glClearColor(1,1,1,1);
    //glClearColor(0.3,0.3,0.3,1.0);

    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    glEnable(GL_NORMALIZE); //mantem a qualidade da iluminacao mesmo quando glScalef eh usada

    glShadeModel(GL_SMOOTH);
    //glShadeModel(GL_FLAT);

    glEnable(GL_DEPTH_TEST);

//    //definindo uma luz
        glEnable(GL_LIGHT0);

        const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
        const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
        const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
        const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

        const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
        const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
        const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
        const GLfloat high_shininess[] = { 100.0f };

        glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);

        glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}

void GLWidget::paintGL()
{
    displayInit();

    //z += 0.001;

    //sistema global
    glPushMatrix();
        //glColor3f(1.0,0,0);
        //glBegin(GL_QUADS);
        //    glVertex3f(0,0,z);
        //    glColor3f(0,0,1);
        //    glVertex3f(1,0,z);
        //    glColor3f(0,1,0);
        //    glVertex3f(1,1,z);
        //    glColor3f(1,1,1);
        //    glVertex3f(0,1,z);
        //glEnd();
        //desenhando eixos do sistema de coordenadas global
          Desenha::drawEixos( 0.5 );
        //chao
        //glColor3d(0.3,0.3,0.3);
        glColor3d(0.3,0.3,0.3);
        Desenha::drawGrid( 5, 0, 1, 1 );
    glPopMatrix();

    //tx += 0.0001;
    //tz -= 0.001;
    //sistema local 1
    glPushMatrix();
        //composicao de transformacoes
        glTranslated(tx,ty,tz);
        glRotated(az,0,0,1);
        glRotated(ay,0,1,0);
        glRotated(ax,1,0,0);
        glScaled(sx,sy,sz);
        //desenhando eixos do sistema de coordenadas local 1
          Desenha::drawEixos( 0.5 );
        //desenhando objeto
        glColor3d(1,0,0);
        glColor3d(r,g,b);
        //glColor3d(0,0,1);
        //glColor3f(1,0.6,0);
        //glutSolidTorus(0.2,0.8,slices,stacks);
        //glutWireTorus(0.2,0.8,slices,stacks);
        //glutSolidTeapot(0.6);
        //glutWireTeapot(0.6);
        Desenha::drawBox( 0.0,0.0,0.0, 1.0,1.0,1.0 );
        //Desenha::drawBox( -1.0,-1.0,-1.0, 1.0,1.0,1.0 );
    glPopMatrix();

    displayEnd();
}

void GLWidget::displayInit()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    const float ar = height>0 ? (float) width / (float) height : 1.0;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.,ar,0.1,1000.);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //definindo posicao e orientacao da camera
    //gluLookAt(0.0,1.0,15.0, 0.0,0.0,-1.0, 0.0,1.0,0.0);
    gluLookAt(cam->e.x,cam->e.y,cam->e.z, cam->c.x,cam->c.y,cam->c.z, cam->u.x,cam->u.y,cam->u.z);
}

void GLWidget::displayEnd()
{

}

void GLWidget::resizeGL(int w, int h)
{
    width = w;
    height = h;
}

void GLWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_Escape:
        case Qt::Key_Return:
        case Qt::Key_Q:
            exit(0);
            break;

        case Qt::Key_A:
            tx += 1.0;
            break;
        case Qt::Key_T:
            trans_obj = !trans_obj;
            break;

        case Qt::Key_Plus:
        case Qt::Key_M:
            slices++;
            stacks++;
            break;

        case Qt::Key_Minus:
        case Qt::Key_N:
            if (slices>3 && stacks>3)
            {
                slices--;
                stacks--;
            }
            break;

    }
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int x = event->x();
    int y = event->y();
    int lx = lastPos.x();
    int ly = lastPos.y();

//    int dx = x - lx;
//    int dy = y - ly;

    if ( (event->buttons() & Qt::LeftButton) && (event->buttons() & Qt::RightButton) ) {
        if (!trans_obj) {
            cam->zoom(y,ly);
        } else {
            tz += 0.01*(y - ly);
            az += -0.1*(x - lx);
        }
    } else if ( (event->buttons() & Qt::LeftButton) && (event->buttons() & Qt::MidButton) ) {
        if (!trans_obj) {
            r += 0.01*(x - lx);
            g += 0.01*(y - ly);
        } else {
            sz += 0.01*(y - ly);
        }
    } else if (event->buttons() & Qt::LeftButton) {
        if (!trans_obj) {
            cam->rotatex(y,ly);
            cam->rotatey(x,lx);
        } else {
            ax += 0.1*(y - ly);
            ay += 0.1*(x - lx);
        }
    } else if (event->buttons() & Qt::RightButton) {
        if (!trans_obj) {
            cam->translatex(x,lx);
            cam->translatey(y,ly);
        } else {
            tx += 0.01*(x - lx);
            ty += -0.01*(y - ly);
        }
    } else if (event->buttons() & Qt::MidButton) {
        if (!trans_obj) {
            b += 0.01*(x - lx);
        } else {
            sx += 0.01*(x - lx);
            sy += -0.01*(y - ly);
        }
    }

    lastPos = event->pos();
}


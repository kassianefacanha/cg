#include <GL/glut.h>
#include <bib/CameraDistante.h>
#include <bib/Desenha.h>

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

bool lbpressed = false;
bool mbpressed = false;
bool rbpressed = false;

float last_x = 0.0;
float last_y = 0.0;

Camera* cam = new CameraDistante();
float savedCamera[9];

void resize(int w, int h)
{
    width = w;
    height = h;
}

void initializeGL()
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

void displayInit()
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

void displayEnd()
{
    glutPostRedisplay();
    glutSwapBuffers();
}

float z = 0.0;
float r = 0.0;
float g = 0.0;
float b = 0.0;

void display(void)
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

void mouseButton(int button, int state, int x, int y) {
    // if the left button is pressed
    if (button == GLUT_LEFT_BUTTON) {
        // when the button is pressed
        if (state == GLUT_DOWN) {
            lbpressed = true;
        } else {// state = GLUT_UP
            lbpressed = false;
        }
    }
    // if the middle button is pressed
    if (button == GLUT_MIDDLE_BUTTON) {
        // when the button is pressed
        if (state == GLUT_DOWN) {
            mbpressed = true;
        } else {// state = GLUT_UP
            mbpressed = false;
        }
    }
    // if the left button is pressed
    if (button == GLUT_RIGHT_BUTTON) {
        // when the button is pressed
        if (state == GLUT_DOWN) {
            rbpressed = true;
        } else {// state = GLUT_UP
            rbpressed = false;
        }
    }

    last_x = x;
    last_y = y;
}

void mouseMove(int x, int y) {
    float fator = 10.0;
    if (lbpressed && !rbpressed && !mbpressed) {
        if (!trans_obj) {
            cam->rotatex(y,last_y);
            cam->rotatey(x,last_x);
        } else {
            ax += (y - last_y)/fator;
            ay += (x - last_x)/fator;
        }
    }
    fator = 100.0;
    if (!lbpressed && rbpressed && !mbpressed) {
        if (!trans_obj) {
            cam->translatex(x,last_x);
            cam->translatey(y,last_y);
        } else {
            tx += (x - last_x)/fator;
            ty += -(y - last_y)/fator;
        }
    }
    if (lbpressed && rbpressed && !mbpressed) {
        if (!trans_obj) {
            cam->zoom(y,last_y);
        } else {
            tz += (y - last_y)/fator;
            fator = 10.0;
            az += -(x - last_x)/fator;
        }
    }
    fator = 100.0;
    if (!lbpressed && !rbpressed && mbpressed) {
        if (!trans_obj) {
            r += (y - last_y)/fator;
            g += (x - last_x)/fator;
        } else {
            sx += (x - last_x)/fator;
            sy += -(y - last_y)/fator;
        }
    }
    if (lbpressed && !rbpressed && mbpressed) {
        if (!trans_obj) {
            b += (y - last_y)/fator;
        } else {
            sz += (y - last_y)/fator;
        }
    }

    last_x = x;
    last_y = y;
}


void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 : //esc
        case 13 : //enter
        case 'q':
            exit(0);
            break;

        case 'F':
            glutFullScreen();
            break;
        case 'f':
            glutReshapeWindow(800,600);
            break;

        case 'z':
            tz -= 0.1;
            break;
        case 'Z':
            tz += 0.1;
            break;

        case 'c':
            r -= 0.1;
            break;
        case 'C':
            r += 0.1;
            break;

        case 'r':
            ay -= 10;
            break;
        case 'R':
            ay += 10;
            break;

        case 't':
            trans_obj = !trans_obj;
            break;

        case '+':
            slices++;
            stacks++;
            break;

        case '-':
            if (slices>3 && stacks>3)
            {
                slices--;
                stacks--;
            }
            break;

    }

    //glutPostRedisplay();
}

void idle(void)
{
    //ty += 0.0001;
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    //chamadas de inicializacao da GLUT
        glutInit(&argc, argv);
        glutInitWindowSize(width,height);
        glutInitWindowPosition(10,10);
        glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

        glutCreateWindow("Primeiro programa OpenGL + GLUT");

        glutReshapeFunc(resize);
        glutDisplayFunc(display);
        glutKeyboardFunc(key);
        glutIdleFunc(idle);

        glutMouseFunc(mouseButton);
        glutMotionFunc(mouseMove);

    //chamadas de inicializacao da OpenGL
        initializeGL();

    //iniciando o loop principal da glut
        glutMainLoop();
}


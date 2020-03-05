#include <iostream>
#include<math.h>
using namespace std;

#include <vector>
#include <lampada.h>
#include <tv.h>
#include <jarro.h>
#include <sofa.h>
#include <mesa.h>
vector<Objeto*> objetos;
vector<Camera*> cameraOrtho;
vector<Camera*> cameraP;
vector<Camera*> cameraOb;
int marcaCameraOb = -1;
int marcaCamera = -1;
int marcaCameraO = -1;
int marcaCameraP = -1;
int posSelecionado = -1;

//-------------------sombra-------------------
bool drawShadow = false;
bool pontual = true;
float k = 0.0;
//-------------------sombra-------------------


void sombra(GLfloat plano[4], GLfloat lightPos[4]){
    glPushMatrix();

            GLfloat sombra[4][4];
            GUI::shadowMatrix(sombra,plano,lightPos);
            glMultTransposeMatrixf( (GLfloat*)sombra );

        glDisable(GL_LIGHTING);
        glColor3d(0.0,0.0,0.0);
        if (drawShadow) {
            bool aux = glutGUI::draw_eixos;
            glutGUI::draw_eixos = false;
            for (int i = 0; i < objetos.size(); ++i) {

                if(objetos[i]->sombra){
                    glPushMatrix();
                        objetos[i]->desenha();
                    glPopMatrix();

                }
            }
            glutGUI::draw_eixos = aux;
        }
        glEnable(GL_LIGHTING);
    glPopMatrix();

}

void desenha() {
    GUI::displayInit();
    GUI::drawOrigin(1);

    GUI::setColor(1,0.5,0.5);
    GUI::drawFloor();
    glPushMatrix();
        //-------------------sombra-------------------
        glTranslated(0.0,k-0.001,0.0);
        //-------------------sombra-------------------
    glPopMatrix();

    for (int i = 0; i < objetos.size(); ++i) {
        glPushMatrix();
            objetos[i]->desenha();
        glPopMatrix();
    }

    //-------------------sombra1-------------------
    //definindo a luz que sera usada para gerar a sombra
    float lightPos[4] = {0+glutGUI::lx,3+glutGUI::ly,3+glutGUI::lz,pontual};
    //GUI::setLight(0,lightPos[0],lightPos[1],lightPos[2],true,false,false,false,pontual);
    GUI::setLight(0,0,3,3,true,false,false,false,pontual);
    //desenhando os objetos projetados
    GLfloat plano[4] = {0,1,0,-0.001}; //{Normal, x, y, z}
    sombra(plano, lightPos);

    //-------------------sombra1-------------------

    //-------------------sombra2-------------------
    //definindo a luz que sera usada para gerar a sombra
    float lightPos2[4] = {0+glutGUI::lx,3+glutGUI::ly,3+glutGUI::lz,pontual};
    //GUI::setLight(0,lightPos[0],lightPos[1],lightPos[2],true,false,false,false,pontual);
    GUI::setLight(0,0,3,3,true,false,false,false,pontual);
    //desenhando os objetos projetados
    GLfloat plano2[4] = {1,0,0,2.49}; //{Normal, x, y, z}
    sombra(plano2, lightPos2);

    //-------------------sombra2-------------------
    //-------------------sombra3-------------------
    //definindo a luz que sera usada para gerar a sombra
    float lightPos3[4] = {0+glutGUI::lx,3+glutGUI::ly,3+glutGUI::lz,pontual};
    //GUI::setLight(0,lightPos[0],lightPos[1],lightPos[2],true,false,false,false,pontual);
    GUI::setLight(0,0,3,3,true,false,false,false,pontual);
    //desenhando os objetos projetados
    GLfloat plano3[4] = {-1,0,0,2.49}; //{Normal, x, y, z}
    sombra(plano3, lightPos3);

    //-------------------sombra3-------------------
    //-------------------sombra4-------------------
    //definindo a luz que sera usada para gerar a sombra
    float lightPos4[4] = {0+glutGUI::lx,3+glutGUI::ly,3+glutGUI::lz,pontual};
    //GUI::setLight(0,lightPos[0],lightPos[1],lightPos[2],true,false,false,false,pontual);
    GUI::setLight(0,0,3,3,true,false,false,false,pontual);
    //desenhando os objetos projetados
    GLfloat plano4[4] = {0,sqrt(2)/2,sqrt(2)/2,1.32}; //{Normal, x, y, z}
    sombra(plano4, lightPos4);

    //-------------------sombra4-------------------

    if (posSelecionado >= 0 and posSelecionado < objetos.size()) {
        objetos[posSelecionado]->t.x += glutGUI::dtx;
        objetos[posSelecionado]->t.y += glutGUI::dty;
        objetos[posSelecionado]->t.z += glutGUI::dtz;

        objetos[posSelecionado]->a.x += glutGUI::dax;
        objetos[posSelecionado]->a.y += glutGUI::day;
        objetos[posSelecionado]->a.z += glutGUI::daz;

        objetos[posSelecionado]->s.x += glutGUI::dsx;
        objetos[posSelecionado]->s.y += glutGUI::dsy;
        objetos[posSelecionado]->s.z += glutGUI::dsz;
    }
    //Parede 1
    glPushMatrix();
    GUI::setColor(0,0,1);
    glBegin(GL_QUADS);
        glNormal3f(0,1,0);
        glVertex3f(2.5,0,2.5);
        glVertex3f(2.5,3.5,2.5);
        glVertex3f(2.5,3.5,-2.5);
        glVertex3f(2.5,0,-2.5);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    GUI::setColor(1,0,1);

    //Parede 2
    //glTranslated(0,1.6,1);
    glRotated(-45,1,0,0);
    glTranslated(0,0,-1.33+2.5);
    glBegin(GL_QUADS);
        glNormal3f(0,0,-1);
        glVertex3f(2.5,0,-2.5);
        glVertex3f(2.5,3.5,-2.5);
        glVertex3f(-2.5,3.5,-2.5);
        glVertex3f(-2.5,0,-2.5);
    glEnd();
    glPopMatrix();
    //Parede 3

    GUI::setColor(1,0,0);

    glBegin(GL_QUADS);
        glNormal3f(1,0,0);
        glVertex3f(-2.5,0,2.5);
        glVertex3f(-2.5,0,-2.5);
        glVertex3f(-2.5,3.5,-2.5);
        glVertex3f(-2.5,3.5,2.5);
    glEnd();
    glPopMatrix();


    cout<<glutGUI::cam->e.x<<','<<glutGUI::cam->e.y<<','<<glutGUI::cam->e.z<<',';
    cout<<glutGUI::cam->c.x<<','<<glutGUI::cam->c.y<<','<<glutGUI::cam->c.z<<',';
    cout<<glutGUI::cam->u.x<<','<<glutGUI::cam->u.y<<','<<glutGUI::cam->u.z<<endl;
    GUI::displayEnd();

}

bool incluirObjeto = true;

void teclado(unsigned char key, int x, int y) {
        GUI::keyInit(key,x,y);

    switch (key) {
        case 't':
            glutGUI::trans_obj = !glutGUI::trans_obj;
            break;
        case 'l':
            glutGUI::trans_luz = !glutGUI::trans_luz;
            break;

        case 'n':
            if (posSelecionado >= 0 and posSelecionado < objetos.size()) {
                objetos[posSelecionado]->selecionado = false;
            }
            posSelecionado++;
            posSelecionado = posSelecionado%objetos.size();
            if (posSelecionado >= 0 and posSelecionado < objetos.size()) {
                objetos[posSelecionado]->selecionado = true;
            }
            break;
        case 'b':
            if (posSelecionado >= 0 and posSelecionado < objetos.size()) {
                objetos[posSelecionado]->selecionado = false;
            }
            posSelecionado--;
            if (posSelecionado < 0) {
                posSelecionado = objetos.size()-1;
            }
            if (posSelecionado >= 0 and posSelecionado < objetos.size()) {
                objetos[posSelecionado]->selecionado = true;
            }
            break;

        case 'p':
            incluirObjeto = !incluirObjeto;
            break;
        case '2':
            if (incluirObjeto) {
                objetos.push_back( new Lampada());
            }
            break;
        case '3':
            if (incluirObjeto) {
                objetos.push_back( new Tv());
            }
            break;
        case '4':
            if(incluirObjeto){
                GUI::drawOrigin(1);
                objetos.push_back(new Sofa());
            }
            break;
        case '5':
            if(incluirObjeto){
                objetos.push_back(new Jarro());
            }
            break;
        case '6':
            if(incluirObjeto){
                objetos.push_back(new Mesa());
            }
            break;
        //-------------------sombra-------------------
        case 's':
            drawShadow = !drawShadow;
            break;
        case 'm':
            pontual = !pontual;
            break;
        case 'K':
            k += 0.1;
            break;
        case 'k':
            k -= 0.1;
            break;

        case 'u':

            if (posSelecionado >= 0 and posSelecionado < objetos.size()) {
             objetos[posSelecionado]->sombra = !objetos[posSelecionado]->sombra;
        }
        //-------------------sombra-------------------

    //________________________________________
        case '=':
            glutGUI::ortho = true;
            glutGUI::perspective= false;
            glutGUI::obliq = false;
            marcaCameraO++;

            if(marcaCameraO>=cameraOrtho.size()){
                marcaCameraO =0;
            }
            glutGUI::cam = new CameraDistante(cameraOrtho[marcaCameraO]->e, cameraOrtho[marcaCameraO]->c, cameraOrtho[marcaCameraO]->u);
            break;
        case '-':
            glutGUI::perspective = true;
            glutGUI::obliq = false;
            glutGUI::ortho = false;
            marcaCameraP++;

            if(marcaCameraP>=cameraP.size()){
                marcaCameraP =0;
            }
            glutGUI::cam = new CameraDistante(cameraP[marcaCameraP]->e, cameraP[marcaCameraP]->c, cameraP[marcaCameraP]->u);
            break;

        case ')':
            glutGUI::obliq = true;
            glutGUI::ortho = false;
            glutGUI::perspective = false;
            marcaCameraOb++;
            if(marcaCameraOb>=cameraOb.size()){
                marcaCameraOb = 0;
            }
            glutGUI::cam = new CameraDistante(cameraOb[marcaCameraOb]->e, cameraOb[marcaCameraOb]->c, cameraOb[marcaCameraOb]->u);
            break;

    //_______________________________________

        default:
            break;
    }
}

int main()
{
    cout << "Hello World!" << endl;
    //isometrica
    cameraOrtho.push_back(new CameraDistante(5.83183,5.56437,6.71984,0,1,0,-0.299168,0.889756,-0.344722));
    //trimetrica
    cameraOrtho.push_back(new CameraDistante(3.47912,3.0497,9.14847,0,1,0,-0.0728583,0.978768,-0.191584));
   //dimetrica
    cameraOrtho.push_back(new CameraDistante(-0.000199788,5.13796,9.10371,0,1,0,9.08104e-06,0.91037,-0.413795));
   //1ponto
   cameraP.push_back(new CameraDistante(4.57603,0.531044,0.0102363,0,1,0,0.101947,0.99479,0.000228048));
   //2ponto
   cameraP.push_back(new CameraDistante(2.57824,0,3.7864,0,1,0,-0.051313,0.995835,-0.0753582));
   //3ponto
   cameraP.push_back(new CameraDistante(3.01227,2.14268,3.28338,0,1,0,-0.167931,0.968656,-0.183046));
   cameraOb.push_back(new CameraDistante(0.950944,1.90821,10.3176,-1.82974,-0.763079,1.09083,-0.0770811,0.963661,-0.255767));

    GUI gui = GUI(800,600,desenha,teclado);
}


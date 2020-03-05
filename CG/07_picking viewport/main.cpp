#include <iostream>

using namespace std;
#include <curva.h>
#include <gui.h>
#include <vector>
#include <lampada.h>
#include <CameraDistante.h>
//-------------------picking------------------
CameraDistante *cam = new CameraDistante();
vector<Vetor3D> pontosControle;
Curva *curva = new Curva();
Lampada *la = new Lampada();
int pontoSelecionado = 0; //names = [1,n] //n = pontosControle.size()
//bool transPontos = glutGUI::trans_obj; //= true;
int matOP = 0;
double delta = 0.01;
bool pessoa = false;
void desenhaPontosDeControle()
{
    //desenhando pontos de controle
    for (int i=0; i<pontosControle.size(); i++) {
        //definindo cor da selecao
        if (i == pontoSelecionado-1) {
            GUI::setColor(1,1,1,1,true);
        } else {
            GUI::setColor(0,0,1,1,true);
        }
        //desenhando (definindo nomes para o picking)
        Vetor3D p = pontosControle[i];
        glPushName(i+1); //não se deve definir name = 0!
            GUI::drawSphere(p.x,p.y,p.z,0.2);
        glPopName();
    }

//    //teste triangulo
//    glBegin(GL_TRIANGLES);
//        glNormal3f(0,0,1); //definir a normal permite ver as cores mais vivas ao posicionar a iluminacao adequadamente
//        GUI::setColor(1,1,1);
//        glVertex3f(0,0,1);
//        GUI::setColor(0,0,1,0.0);
//        glVertex3f(2,0,1);
//        GUI::setColor(0,1,0,0.0);
//        glVertex3f(0,2,1);
//    glEnd();
//    //teste triangulo usando glColor (sem iluminacao)
//    glDisable(GL_LIGHTING);
//    glBegin(GL_TRIANGLES);
//        glNormal3f(0,0,1);
//        glColor4f(0,1,0,1);
//        glVertex3f(-1,2,1);
//        glColor4f(0,0,1,1);
//        glVertex3f(-3,0,1);
//        glColor4f(1,1,1,0);
//        glVertex3f(-1,0,1);
//    glEnd();
//    glEnable(GL_LIGHTING);
}

//picking
int picking( GLint cursorX, GLint cursorY, int w, int h ) {
    int BUFSIZE = 512;
    GLuint selectBuf[512];

    GUI::pickingInit(cursorX,cursorY,w,h,selectBuf,BUFSIZE);

//de acordo com a implementacao original da funcao display
    //lembrar de nao inicializar a matriz de projecao, para nao ignorar a gluPickMatrix
    GUI::displayInit();
    //só precisa desenhar o que for selecionavel
    desenhaPontosDeControle();
//fim-de acordo com a implementacao original da funcao display

    //retornando o name do objeto (ponto de controle) mais proximo da camera (z minimo! *[matrizes de normalizacao da projecao])
    return GUI::pickingClosestName(selectBuf,BUFSIZE);
}
//-------------------picking------------------

//-------------------viewPorts------------------
bool viewports = false;
bool scissored = false;

void cenario();

//visao de duas cameras (duas viewports), viewport auxiliar sobrepondo a principal
void viewPorts() {
    float width = glutGUI::width;
    float height = glutGUI::height;

    //viewport principal
    glViewport(0, 0, width, height);
        glLoadIdentity();
        gluLookAt(glutGUI::cam->e.x,glutGUI::cam->e.y,glutGUI::cam->e.z, glutGUI::cam->c.x,glutGUI::cam->c.y,glutGUI::cam->c.z, glutGUI::cam->u.x,glutGUI::cam->u.y,glutGUI::cam->u.z);
            cenario();

    //viewport auxiliar sobrepondo a principal
    if (!scissored) {
        //misturando com a principal
        glViewport(0, 3*height/4, width/4, height/4);
    } else {
        //recortando/substituindo o pedaço
        GUI::glScissoredViewport(0, 3*height/4, width/4, height/4);
    }
        glLoadIdentity();
        //Vetor3D eye = pontosControle[4];
        //Vetor3D center = pontosControle[2];
        if(pessoa){
             gluLookAt(cam->e.x,cam->e.y,cam->e.z, cam->c.x,cam->c.y,cam->c.z, cam->u.x,cam->u.y,cam->u.z);
        }
        else{
               gluLookAt(curva->camPro->e.x,curva->camPro->e.y,curva->camPro->e.z, curva->camPro->c.x,curva->camPro->c.y,curva->camPro->c.z, curva->camPro->u.x,curva->camPro->u.y,curva->camPro->u.z);
     }
            cenario();
}
//-------------------viewPorts------------------

void cenario() {
    //GUI::setLight(1,1,3,5,true,false);
    //GUI::setLight(2,-1.5,0.5,-1,true,false);
    GUI::setLight(3,-5,3,5,true,false);

    GUI::drawOrigin(0.5);

    //GUI::setColor(1,0,0);
    //GUI::drawFloor();
    GUI::setColor(0,0,0);
    Desenha::drawGrid( 5, 0, 1, 1 );

    desenhaPontosDeControle();
    curva->DesCurva(pontosControle, 0.01);
    curva->desenhaO(pontosControle, delta, cam);
}

void desenha() {
    GUI::displayInit();

    if (!viewports) {
        cenario();
    } else {
        viewPorts();
    }

    //transladando ponto selecionado atraves do picking
    //if (pontoSelecionado > 0 and pontoSelecionado <= objetos.size()) {
    if (pontoSelecionado!=0) {
        pontosControle[pontoSelecionado-1].x += glutGUI::dtx;
        pontosControle[pontoSelecionado-1].y += glutGUI::dty;
        pontosControle[pontoSelecionado-1].z += glutGUI::dtz;
    }

    GUI::displayEnd();
}

void teclado(unsigned char key, int x, int y) {
    GUI::keyInit(key,x,y);

    switch (key) {
    case 't':
        glutGUI::trans_obj = !glutGUI::trans_obj;
        //transPontos = glutGUI::trans_obj;
        break;
    case 'l':
        glutGUI::trans_luz = !glutGUI::trans_luz;
        break;

    case 'v':
        viewports = !viewports;
        break;
    case 's':
        scissored = !scissored;
        break;
    case 'p':
        pontosControle.push_back(Vetor3D(0,0,0) );
        break;
    case 'u':
        pontosControle.pop_back();
        break;
    case 'e':
        delta = 0.01;
        break;
    case 'r':
        delta = -0.01;
        break;
    case 'n':
        pessoa = !pessoa;
        break;
    case 'a':
           matOP  = (matOP + 1)%5;
           if(matOP==0){
               curva->Matriz=curva->Interpoladora;
           }else if(matOP==1){
               curva->Matriz=curva->Hermite;
           }else if(matOP==2){
               curva->Matriz=curva->Bezier;
           }else if(matOP==3){
               curva->Matriz=curva->CatmullRom;
           }else{
               curva->Matriz=curva->Bspline;
           }
           break;

    default:
        break;
    }
}

void mouse(int button, int state, int x, int y) {
    GUI::mouseButtonInit(button,state,x,y);

    // if the left button is pressed
    if (button == GLUT_LEFT_BUTTON) {
        // when the button is pressed
        if (state == GLUT_DOWN) {
            //picking
            int pick = picking( x, y, 5, 5 );
            if (pick != 0) {
                pontoSelecionado = pick;
                glutGUI::lbpressed = false;
            }
        }
    }
}

int main()
{
    cout << "Hello World!" << endl;
    int n = 5;
    float dist = 1.0;
//    for (int i=0; i<n; i++) {
//        pontosControle.push_back( Vetor3D((i-n/2)*dist,1,0) );
//   }
    pontosControle.push_back(Vetor3D(-2,2,0) );
    pontosControle.push_back(Vetor3D(2,2,0) );
    pontosControle.push_back(Vetor3D(2,-2,0) );
    pontosControle.push_back(Vetor3D(-2,-2,0) );

    GUI gui = GUI(800,600,desenha,teclado,mouse);
}


//while(true) {
//    desenha();
//    interacaoUsuario();
//}

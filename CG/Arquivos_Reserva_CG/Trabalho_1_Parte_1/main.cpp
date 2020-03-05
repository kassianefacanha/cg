#include <iostream>

using namespace std;

#include <vector>
#include <lampada.h>
#include <tv.h>
#include <jarro.h>
#include <sofa.h>
#include <mesa.h>
vector<Objeto*> objetos;
int posSelecionado = -1;

void desenha() {
    GUI::displayInit();

    GUI::setLight(1,0,8,0,true,false);

    GUI::drawOrigin(1);

    GUI::setColor(1,0.5,0.5);
    GUI::drawFloor();

    for (int i = 0; i < objetos.size(); ++i) {
        glPushMatrix();
            objetos[i]->desenha();
        glPopMatrix();
    }

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
        default:
            break;
    }
}

int main()
{
    cout << "Hello World cccc!" << endl;

    GUI gui = GUI(800,600,desenha,teclado);
}


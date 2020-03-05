#include "lampada.h"

Lampada::Lampada()
{

}

void Lampada::desenha()
{
    glPushMatrix();
        Objeto::desenha();

     if (selecionado) {
         GUI::setColor(1,0,0);
     } else {
         GUI::setColor(0.8,0.8,0.8);
     }
     GUI::setLight(0,0,3,0,true,false);
     //face frente
     glBegin(GL_QUADS);
         glNormal3f(0,0,1);
         glVertex3f(-0.2,3.1,0.2);
         glVertex3f(0.2,3.1,0.2);
         glVertex3f(0.5,3.5,0.5);
         glVertex3f(-0.5,3.5,0.5);
     glEnd();
     //face direira
     glBegin(GL_QUADS);
         glNormal3f(1,0,0);
         glVertex3f(0.2,3.1,0.2);
         glVertex3f(0.2,3.1,-0.2);
         glVertex3f(0.5,3.5,-0.5);
         glVertex3f(0.5,3.5,0.5);
     glEnd();
     //face tras
     glBegin(GL_QUADS);
         glNormal3f(0,0,-1);
         glVertex3f(0.2,3.1,-0.2);
         glVertex3f(-0.2,3.1,-0.2);
         glVertex3f(-0.5,3.5,-0.5);
         glVertex3f(0.5,3.5,-0.5);
     glEnd();
     //face esquerda
     glBegin(GL_QUADS);
         glNormal3f(-1,0,0);
         glVertex3f(-0.2,3.1,-0.2);
         glVertex3f(-0.2,3.1,0.2);
         glVertex3f(-0.5,3.5,0.5);
         glVertex3f(-0.5,3.5,-0.5);
     glEnd();
     //face superior
     glBegin(GL_QUADS);
         glNormal3f(0,0,0);
         glVertex3f(0.5,3.5,0.5);
         glVertex3f(0.5,3.5,-0.5);
         glVertex3f(-0.5,3.5,-0.5);
         glVertex3f(-0.5,3.5,0.5);
     glEnd();
     //face inferior
     glBegin(GL_QUADS);
         glNormal3f(0,0,0);
         glVertex3f(0.2,3.1,0.2);
         glVertex3f(-0.2,3.1,0.2);
         glVertex3f(-0.2,3.1,-0.2);
         glVertex3f(0.2,3.1,-0.2);
     glEnd();
    glPopMatrix();
}

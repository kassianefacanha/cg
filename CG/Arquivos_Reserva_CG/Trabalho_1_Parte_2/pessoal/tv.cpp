#include "tv.h"

Tv::Tv()
{

}

void Tv::desenha()
{
    glPushMatrix();
        Objeto::desenha();
        if (selecionado) {
            GUI::setColor(1,0,0);
            //face frente
            glBegin(GL_QUADS);
                glNormal3f(0,0,1);
                glVertex3f(2,1,1);
                glVertex3f(2.1,1,1);
                glVertex3f(2.1,2,1);
                glVertex3f(2,2,1);
            glEnd();
            //face tras
            glBegin(GL_QUADS);
                glNormal3f(0,0,-1);
                glVertex3f(2,1,-1);
                glVertex3f(2,2,-1);
                glVertex3f(2.1,2,-1);
                glVertex3f(2.1,1,-1);
            glEnd();
            //face direita
            glBegin(GL_QUADS);
                glNormal3f(1,0,0);
                glVertex3f(2.1,1,1);
                glVertex3f(2.1,1,-1);
                glVertex3f(2.1,2,-1);
                glVertex3f(2.1,2,1);
            glEnd();
            //face esquerda
            glBegin(GL_QUADS);
                glNormal3f(-1,0,0);
                glVertex3f(2,1,1);
                glVertex3f(2,2,1);
                glVertex3f(2,2,-1);
                glVertex3f(2,1,-1);
            glEnd();
            //face superior
            glBegin(GL_QUADS);
                glNormal3f(0,1,0);
                glVertex3f(2,2,1);
                glVertex3f(2.1,2,1);
                glVertex3f(2.1,2,-1);
                glVertex3f(2,2,-1);
            glEnd();
            //face inferior
            glBegin(GL_QUADS);
                glNormal3f(0,-1,0);
                glVertex3f(2,1,1);
                glVertex3f(2,1,-1);
                glVertex3f(2.1,1,-1);
                glVertex3f(2.1,1,1);
            glEnd();
            //frente do tubo
            glBegin(GL_QUADS);
                glNormal3f(1,0,0);
                glVertex3f(2.1,1.1,0.6);
                glVertex3f(2.2,1.2,0.5);
                glVertex3f(2.2,1.8,0.5);
                glVertex3f(2.1,1.9,0.6);
            glEnd();
            //tras do tubo
            glBegin(GL_QUADS);
                glNormal3f(1,0,0);
                glVertex3f(2.1,1.1,-0.6);
                glVertex3f(2.1,1.9,-0.6);
                glVertex3f(2.2,1.8,-0.5);
                glVertex3f(2.2,1.2,-0.5);
            glEnd();
            //direita do tubo
            glBegin(GL_QUADS);
                glNormal3f(1,0,0);
                glVertex3f(2.2,1.2,0.5);
                glVertex3f(2.2,1.2,-0.5);
                glVertex3f(2.2,1.8,-0.5);
                glVertex3f(2.2,1.8,0.5);
            glEnd();
            //superior do tubo
            glBegin(GL_QUADS);
                glNormal3f(1,0,0);
                glVertex3f(2.1,1.9,0.6);
                glVertex3f(2.2,1.8,0.5);
                glVertex3f(2.2,1.8,-0.5);
                glVertex3f(2.1,1.9,-0.6);
            glEnd();
            //inferior do tubo
            glBegin(GL_QUADS);
                glNormal3f(1,0,0);
                glVertex3f(2.1,1.1,0.6);
                glVertex3f(2.1,1.1,-0.6);
                glVertex3f(2.2,1.2,-0.5);
                glVertex3f(2.2,1.2,0.5);
            glEnd();

        } else {
            GUI::setColor(0,0,0);
            //face frente
            glBegin(GL_QUADS);
                glNormal3f(0,0,1);
                glVertex3f(2,1,1);
                glVertex3f(2.1,1,1);
                glVertex3f(2.1,2,1);
                glVertex3f(2,2,1);
            glEnd();
            //face tras
            glBegin(GL_QUADS);
                glNormal3f(0,0,-1);
                glVertex3f(2,1,-1);
                glVertex3f(2,2,-1);
                glVertex3f(2.1,2,-1);
                glVertex3f(2.1,1,-1);
            glEnd();
            //face direita
            glBegin(GL_QUADS);
                glNormal3f(1,0,0);
                glVertex3f(2.1,1,1);
                glVertex3f(2.1,1,-1);
                glVertex3f(2.1,2,-1);
                glVertex3f(2.1,2,1);
            glEnd();
            //face esquerda
            glBegin(GL_QUADS);
                glNormal3f(-1,0,0);
                glVertex3f(2,1,1);
                glVertex3f(2,2,1);
                glVertex3f(2,2,-1);
                glVertex3f(2,1,-1);
            glEnd();
            //face superior
            glBegin(GL_QUADS);
                glNormal3f(0,1,0);
                glVertex3f(2,2,1);
                glVertex3f(2.1,2,1);
                glVertex3f(2.1,2,-1);
                glVertex3f(2,2,-1);
            glEnd();
            //face inferior
            glBegin(GL_QUADS);
                glNormal3f(0,-1,0);
                glVertex3f(2,1,1);
                glVertex3f(2,1,-1);
                glVertex3f(2.1,1,-1);
                glVertex3f(2.1,1,1);
            glEnd();
            GUI::setColor(1,1,1);
            //frente do tubo
            glBegin(GL_QUADS);
                glNormal3f(1,0,0);
                glVertex3f(2.1,1.1,0.6);
                glVertex3f(2.2,1.2,0.5);
                glVertex3f(2.2,1.8,0.5);
                glVertex3f(2.1,1.9,0.6);
            glEnd();
            //tras do tubo
            glBegin(GL_QUADS);
                glNormal3f(1,0,0);
                glVertex3f(2.1,1.1,-0.6);
                glVertex3f(2.1,1.9,-0.6);
                glVertex3f(2.2,1.8,-0.5);
                glVertex3f(2.2,1.2,-0.5);
            glEnd();
            //direita do tubo
            glBegin(GL_QUADS);
                glNormal3f(1,0,0);
                glVertex3f(2.2,1.2,0.5);
                glVertex3f(2.2,1.2,-0.5);
                glVertex3f(2.2,1.8,-0.5);
                glVertex3f(2.2,1.8,0.5);
            glEnd();
            //superior do tubo
            glBegin(GL_QUADS);
                glNormal3f(1,0,0);
                glVertex3f(2.1,1.9,0.6);
                glVertex3f(2.2,1.8,0.5);
                glVertex3f(2.2,1.8,-0.5);
                glVertex3f(2.1,1.9,-0.6);
            glEnd();
            //inferior do tubo
            glBegin(GL_QUADS);
                glNormal3f(1,0,0);
                glVertex3f(2.1,1.1,0.6);
                glVertex3f(2.1,1.1,-0.6);
                glVertex3f(2.2,1.2,-0.5);
                glVertex3f(2.2,1.2,0.5);
            glEnd();

        }

    glPopMatrix();
}

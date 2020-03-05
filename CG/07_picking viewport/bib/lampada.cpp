#include "lampada.h"

Lampada::Lampada()
{

}

void Lampada::desenha()
{
    GUI::setColor(1,0,0);
    glPushMatrix();
        GUI::drawBox(-1,-1,1 , 1,1,-1);
    glPopMatrix();
}

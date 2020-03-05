#include "jarro.h"

Jarro::Jarro()
{
    model=new Model3DS("../3ds/Statue.3DS");

}
void Jarro::desenha(){

    glPushMatrix();
        Objeto::desenha();
        glTranslated(2,0,-2);
        glRotatef(-90,1,0,0);
        glRotated(-45,0,0,1);
        glScalef(0.005,0.005,0.005);

        model->draw();
    glPopMatrix();
}

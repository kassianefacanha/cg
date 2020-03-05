#include "sofa.h"

Sofa::Sofa()
{
    model=new Model3DS("../3ds/Sofa 2.3ds");
}


void Sofa::desenha(){

    glPushMatrix();
        Objeto::desenha();
        glTranslated(0,0.34,0);
        glRotatef(90,0,1,0);
        glRotatef(-90,1,0,0);
        glScalef(0.0008,0.0008,0.0008);

        model->draw();
    glPopMatrix();
}

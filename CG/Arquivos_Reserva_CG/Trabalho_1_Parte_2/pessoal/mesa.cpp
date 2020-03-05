#include "mesa.h"

Mesa::Mesa()
{
    model=new Model3DS("../3ds/Table.3ds");
}

void Mesa::desenha(){
    glPushMatrix();
        Objeto::desenha();
        glTranslated(0,0.2,0);
        glRotatef(-90,1,0,0);
        glRotatef(40,0,0,1);
        glScalef(0.013,0.009,0.013);

        model->draw();
    glPopMatrix();
}

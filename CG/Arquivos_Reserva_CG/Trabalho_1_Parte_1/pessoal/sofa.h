#ifndef SOFA_H
#define SOFA_H

#include <objeto.h>

class Sofa : public Objeto
{
public:
    Model3DS* model;

public:
    Sofa();
    void desenha();
};

#endif // SOFA_H

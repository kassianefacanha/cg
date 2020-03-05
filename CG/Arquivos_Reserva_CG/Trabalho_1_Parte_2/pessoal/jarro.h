#ifndef JARRO_H
#define JARRO_H
#include <objeto.h>

class Jarro: public Objeto
{
public:
    Model3DS* model;

public:
    Jarro();
    void desenha();
};

#endif // JARRO_H

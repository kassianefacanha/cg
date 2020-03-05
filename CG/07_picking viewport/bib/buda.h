#ifndef BUDA_H
#define BUDA_H
#include <objeto.h>

class Buda: public Objeto
{
public:
    Model3DS* model;

public:

    Buda();
    void desenha();
};

#endif // BUDA_H

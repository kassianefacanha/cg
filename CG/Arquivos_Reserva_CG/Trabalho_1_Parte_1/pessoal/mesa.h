#ifndef MESA_H
#define MESA_H

#include <objeto.h>

class Mesa : public Objeto
{
public:
    Model3DS* model;

public:
    Mesa();
    void desenha();
};

#endif // MESA_H

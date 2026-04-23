#ifndef BOMBO_H
#define BOMBO_H

#include <iostream>
#include "Lista.h"

using namespace std;

class Equipo;

class Bombo
{
private:
    int numero;
    Lista<Equipo*> equipos;

public:
    Bombo();
    Bombo(int numero);
    Bombo(const Bombo& otro);
    ~Bombo();

    int getNumero() const;
    int getTamano() const;
    bool vacio() const;

    void agregar(Equipo* equipo);
    Equipo* extraerAleatorio();
    void devolver(Equipo* equipo);

    friend ostream& operator<<(ostream& os, const Bombo& b);
};

#endif

//Necesario implementar Lista

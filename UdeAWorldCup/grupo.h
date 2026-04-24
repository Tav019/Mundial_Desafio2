#ifndef GRUPO_H
#define GRUPO_H

#include <iostream>
#include "Lista.h"

using namespace std;

class Equipo;
class Partido;

class Grupo
{
private:
    char letra;
    Lista<Equipo*> equipos;
    Lista<Partido*> partidos;

    int buscarEquipo(Equipo* equipo) const;
    Lista<Equipo*> ordenarEquipos() const;

public:
    Grupo();
    Grupo(char letra);
    Grupo(const Grupo& otro);
    ~Grupo();

    char getLetra() const;
    Lista<Equipo*>& getEquipos();
    Lista<Partido*>& getPartidos();

    void agregarEquipo(Equipo* equipo);
    void agregarPartido(Partido* partido);

    Equipo* getPrimero() const;
    Equipo* getSegundo() const;
    Equipo* getTercero() const;

    friend ostream& operator<<(ostream& os, const Grupo& g);
};

#endif

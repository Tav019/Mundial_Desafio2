#ifndef GRUPO_H
#define GRUPO_H

#include <iostream>
#include "Lista.h"
#include "equipo.h"
#include "partido.h"

using namespace std;

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
    const Lista<Equipo*>& getEquipos() const;
    Lista<Partido*>& getPartidos();
    const Lista<Partido*>& getPartidos() const;

    bool validarConfederacion(Equipo* equipo) const;
    bool agregarEquipo(Equipo* equipo);
    bool agregarPartido(Partido* partido);
    void simularPartidos();

    int getPuntosDeEquipo(Equipo* equipo) const;
    int getGolesFavorGrupo(Equipo* equipo) const;
    int getGolesContraGrupo(Equipo* equipo) const;
    int getDiferenciaGolGrupo(Equipo* equipo) const;

    Equipo* getPrimero() const;
    Equipo* getSegundo() const;
    Equipo* getTercero() const;

    void imprimirTabla(ostream& os) const;
    void imprimirPartidos(ostream& os) const;

    friend ostream& operator<<(ostream& os, const Grupo& grupo);
};

#endif

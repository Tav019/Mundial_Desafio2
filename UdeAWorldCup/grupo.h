#ifndef GRUPO_H
#define GRUPO_H

#include <iostream>
#include <string>

#include "Lista.h"
#include "equipo.h"
#include "fecha.h"

class Partido;

class Grupo
{
private:
    char letra;
    Lista<Equipo*> equipos;
    Lista<Partido*> partidos;

    int buscarEquipo(Equipo* equipo) const;

public:
    Grupo();
    Grupo(char letra);
    Grupo(const Grupo& otro);
    ~Grupo();

    char getLetra() const;
    Lista<Equipo*>& getEquipos();
    Lista<Partido*>& getPartidos();

    bool validarConfederacion(Equipo* equipo) const;
    bool agregarEquipo(Equipo* equipo);
    void agregarPartido(Partido* partido);
    void generarPartidos(const Fecha& fechaBase, const std::string& etapa);
    void simularPartidos();
    Lista<Equipo*> ordenarEquipos() const;
    Equipo* getPrimero() const;
    Equipo* getSegundo() const;
    Equipo* getTercero() const;
    void imprimirTabla(std::ostream& os) const;
    void imprimirPartidos(std::ostream& os) const;

    friend std::ostream& operator<<(std::ostream& os, const Grupo& grupo);
};

#endif

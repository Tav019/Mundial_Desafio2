#ifndef TORNEO_H
#define TORNEO_H

#include <iostream>
#include <string>

#include "Lista.h"
#include "equipo.h"
#include "grupo.h"
#include "partido.h"
#include "recursos.h"

class Torneo
{
private:
    std::string nombre;
    Lista<Equipo*> equipos;
    Lista<Equipo*> bombo1;
    Lista<Equipo*> bombo2;
    Lista<Equipo*> bombo3;
    Lista<Equipo*> bombo4;
    Lista<Grupo*> grupos;
    Lista<Partido*> partidos;
    Lista<Equipo*> clasificadosR16;
    Lista<Equipo*> clasificadosR8;
    Lista<Equipo*> clasificadosR4;
    Lista<Equipo*> finalistas;
    Equipo* campeon;
    Equipo* subcampeon;
    Equipo* tercerLugar;
    Equipo* cuartoLugar;
    Recursos recursos;

    void limpiarBombos();
    void limpiarClasificados();
    void ordenarEquiposPorRanking(Lista<Equipo*>& lista) const;
    Equipo* extraerAleatorioDeLista(Lista<Equipo*>& lista);

public:
    Torneo();
    Torneo(const std::string& nombre);
    ~Torneo();

    void agregarEquipo(Equipo* equipo);
    void cargarDatosEquipos(const std::string& archivo);
    void crearJugadoresArtificiales();
    void guardarDatosJugadores(const std::string& archivo);
    void crearBombos();
    Equipo* extraerEquipoDeBombo(int numeroBombo);
    void formarGrupos();
    void configurarPartidosGrupos();
    void simularFaseGrupos();
    void clasificarADieciseisavos();

    const Lista<Equipo*>& getEquipos() const;
    const Lista<Grupo*>& getGrupos() const;
    const Lista<Partido*>& getPartidos() const;
    const Lista<Equipo*>& getClasificadosR16() const;
    Recursos& getRecursos();
    const Recursos& getRecursos() const;

    void mostrarRecursos(std::ostream& os) const;
};

#endif

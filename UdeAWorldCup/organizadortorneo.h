#ifndef ORGANIZADORTORNEO_H
#define ORGANIZADORTORNEO_H

#include <string>

using namespace std;

#include "Lista.h"
#include "equipo.h"
#include "grupo.h"
#include "recursos.h"

class OrganizadorTorneo
{
private:
    static void ordenarEquiposPorRanking(Lista<Equipo*>& lista);
    static Lista<Equipo*>* obtenerBombo(int numeroBombo, Lista<Equipo*>& bombo1, Lista<Equipo*>& bombo2,
        Lista<Equipo*>& bombo3, Lista<Equipo*>& bombo4);
    static int buscarIndiceEquipo(Lista<Equipo*>& lista, Equipo* equipo);
    static bool asignarEquiposAGrupos(Lista<Grupo*>& grupos, Lista<Equipo*>& bombo1, Lista<Equipo*>& bombo2,
        Lista<Equipo*>& bombo3, Lista<Equipo*>& bombo4,int indiceSlot, Recursos& recursos);

public:
    static bool cargarEquiposDesdeCSV(const string& archivo, Lista<Equipo*>& equipos);
    static void crearBombos(Lista<Equipo*>& equipos,Lista<Equipo*>& bombo1, Lista<Equipo*>& bombo2,
        Lista<Equipo*>& bombo3,Lista<Equipo*>& bombo4);
    static bool gruposCompletosYValidos(Lista<Grupo*>& grupos);
    static bool formarGrupos(Lista<Grupo*>& grupos, Lista<Equipo*>& bombo1, Lista<Equipo*>& bombo2,
        Lista<Equipo*>& bombo3, Lista<Equipo*>& bombo4,Recursos& recursos);
};

#endif

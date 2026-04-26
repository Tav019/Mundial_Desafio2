#ifndef TORNEO_H
#define TORNEO_H

#include <iostream>
#include <string>

using namespace std;

#include "Lista.h"
#include "equipo.h"
#include "grupo.h"
#include "partido.h"
#include "recursos.h"

class Torneo
{
private:
    string nombre;
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
    Lista<Equipo*> semifinalistas;
    Lista<Equipo*> finalistas;
    Equipo* campeon;
    Equipo* subcampeon;
    Equipo* tercerLugar;
    Equipo* cuartoLugar;
    Recursos recursos;

    bool datosCargados;
    bool jugadoresCreados;
    bool bombosCreados;
    bool gruposFormados;
    bool partidosGruposConfigurados;
    bool faseGruposSimulada;
    bool dieciseisavosConfigurados;
    bool eliminatoriasSimuladas;

    void liberarTodo();
    void limpiarBombos();
    void limpiarClasificados();
    void ordenarEquiposPorRanking(Lista<Equipo*>& lista) const;
    void ordenarEquiposPorDesempeno(Lista<Equipo*>& lista, bool descendente) const;
    Equipo* extraerAleatorioDeLista(Lista<Equipo*>& lista);
    Grupo* buscarGrupoDeEquipo(Equipo* equipo) const;
    Lista<Equipo*>* obtenerBombo(int numeroBombo);
    bool mismoGrupo(Equipo* a, Equipo* b) const;
    int buscarIndiceEquipo(const Lista<Equipo*>& lista, Equipo* equipo) const;
    bool asignarEquiposAGrupos(int indiceSlot);
    bool gruposCompletosYValidos() const;
    bool emparejarDieciseisavos(const Lista<Equipo*>& disponibles, Lista<Equipo*>& cuadro) const;
    void agregarPareja(Lista<Equipo*>& destino, Equipo* a, Equipo* b);
    Partido* registrarPartido(Equipo* equipo1, Equipo* equipo2, const Fecha& fecha, const string& etapa);
    void simularRonda(const Lista<Equipo*>& participantes, Lista<Equipo*>& ganadores, const string& etapa, const Fecha& fechaBase, Lista<Equipo*>* perdedores);
    long estimarMemoriaActual() const;
    void actualizarMemoria();
    int indiceConfederacion(const Lista<string>& nombres, const string& confederacion) const;
    void mostrarConfederacionMayor(const Lista<Equipo*>& lista, const string& etapa, ostream& os) const;

public:
    Torneo();
    Torneo(const string& nombre);
    ~Torneo();

    void agregarEquipo(Equipo* equipo);
    void cargarDatosEquipos(const string& archivo);
    void crearJugadoresArtificiales();
    void guardarDatosJugadores(const string& archivo);
    void crearBombos();
    Equipo* extraerEquipoDeBombo(int numeroBombo);
    void formarGrupos();
    void configurarPartidosGrupos();
    void simularFaseGrupos();
    void clasificarADieciseisavos();
    void configurarDieciseisavos();
    void simularEliminatorias();
    void generarEstadisticasFinales(ostream& os) const;
    void mostrarRecursos(ostream& os) const;
    void menu();

    const Lista<Equipo*>& getEquipos() const;
    const Lista<Grupo*>& getGrupos() const;
    const Lista<Partido*>& getPartidos() const;
    const Lista<Equipo*>& getClasificadosR16() const;
    const Lista<Equipo*>& getClasificadosR8() const;
    const Lista<Equipo*>& getClasificadosR4() const;
    Recursos& getRecursos();
    const Recursos& getRecursos() const;
};

#endif

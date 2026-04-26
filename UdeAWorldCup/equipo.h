#ifndef EQUIPO_H
#define EQUIPO_H

#include <iostream>
#include <string>

using namespace std;

#include "Lista.h"
#include "jugador.h"

class Equipo
{
private:
    string pais;
    string directorTecnico;
    string federacion;
    string confederacion;
    int rankingFIFA;
    int golesFavor;
    int golesContra;
    int partidosGanados;
    int partidosEmpatados;
    int partidosPerdidos;
    int tarjetasAmarillas;
    int tarjetasRojas;
    int faltas;
    int puntosGrupo;
    Lista<Jugador*> jugadores;

public:
    Equipo();
    Equipo(const string& pais, int rankingFIFA, const string& confederacion);
    Equipo(const string& pais,
           const string& directorTecnico,
           const string& federacion,
           const string& confederacion,
           int rankingFIFA,
           int golesFavor,
           int golesContra,
           int partidosGanados,
           int partidosEmpatados,
           int partidosPerdidos);
    Equipo(const Equipo& otro);
    ~Equipo();

    string getPais() const;
    string getDirectorTecnico() const;
    string getFederacion() const;
    string getConfederacion() const;
    int getRankingFIFA() const;
    int getGolesFavor() const;
    int getGolesContra() const;
    int getDiferenciaGol() const;
    int getPartidosGanados() const;
    int getPartidosEmpatados() const;
    int getPartidosPerdidos() const;
    int getPartidosTotales() const;
    int getTarjetasAmarillas() const;
    int getTarjetasRojas() const;
    int getFaltas() const;
    int getPuntosGrupo() const;

    void setDirectorTecnico(const string& directorTecnico);
    void setFederacion(const string& federacion);
    void setConfederacion(const string& confederacion);
    void setRankingFIFA(int rankingFIFA);

    void agregarJugador(Jugador* jugador);
    Jugador* getJugador(int posicion) const;
    int getCantidadJugadores() const;
    Lista<Jugador*>& getJugadores();
    const Lista<Jugador*>& getJugadores() const;

    void actualizarEstadisticas(int gf, int gc, int amarillas, int rojas, int faltas);
    void sumarPuntos(int puntos);
    void reiniciarPuntosGrupo();

    bool operator<(const Equipo& otro) const;
    bool operator==(const Equipo& otro) const;

    friend ostream& operator<<(ostream& os, const Equipo& equipo);
};

#endif

#ifndef EQUIPO_H
#define EQUIPO_H

#include <iostream>
#include <string>

#include "Lista.h"
#include "jugador.h"

class Equipo
{
private:
    // Estos atributos guardan la identidad del equipo y su histórico acumulado.
    std::string pais;
    std::string directorTecnico;
    std::string federacion;
    std::string confederacion;
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
    // La plantilla se almacena con memoria dinámica y punteros para manejar composición.
    Lista<Jugador*> jugadores;

public:
    Equipo();
    Equipo(const std::string& pais, int ranking, const std::string& confederacion);
    Equipo(const std::string& pais,
           const std::string& directorTecnico,
           const std::string& federacion,
           const std::string& confederacion,
           int ranking,
           int golesFavor,
           int golesContra,
           int ganados,
           int empatados,
           int perdidos);
    Equipo(const Equipo& otro);
    ~Equipo();

    std::string getPais() const;
    std::string getDirectorTecnico() const;
    std::string getFederacion() const;
    std::string getConfederacion() const;
    int getRankingFIFA() const;
    int getPuntosGrupo() const;
    int getGolesFavor() const;
    int getGolesContra() const;
    int getDiferenciaGol() const;
    int getPartidosTotales() const;
    int getTarjetasAmarillas() const;
    int getTarjetasRojas() const;
    int getFaltas() const;

    void setDirectorTecnico(const std::string& directorTecnico);
    void setFederacion(const std::string& federacion);
    void setRankingFIFA(int rankingFIFA);
    void agregarJugador(Jugador* jugador);
    Jugador* getJugador(int pos) const;
    int getCantidadJugadores() const;
    Lista<Jugador*>& getJugadores();
    const Lista<Jugador*>& getJugadores() const;
    void actualizarEstadisticas(int gf, int gc, int amarillas, int rojas, int faltas);
    void sumarPuntos(int puntos);
    void reiniciarPuntosGrupo();

    bool operator<(const Equipo& otro) const;
    bool operator==(const Equipo& otro) const;

    friend std::ostream& operator<<(std::ostream& os, const Equipo& equipo);
};

#endif

#ifndef REGISTROJUGADORPARTIDO_H
#define REGISTROJUGADORPARTIDO_H

#include <iostream>
#include "jugador.h"

using namespace std;

class RegistroJugadorPartido
{
private:
    Jugador* jugador;
    int goles;
    int tarjetasAmarillas;
    int tarjetasRojas;
    int faltas;
    int minutosJugados;

public:
    RegistroJugadorPartido();
    RegistroJugadorPartido(Jugador* jugador);
    RegistroJugadorPartido(const RegistroJugadorPartido& otro);
    ~RegistroJugadorPartido();

    Jugador* getJugador() const;
    int getGoles() const;
    int getTarjetasAmarillas() const;
    int getAmarillas() const;
    int getTarjetasRojas() const;
    int getRojas() const;
    int getFaltas() const;
    int getMinutosJugados() const;
    int getMinutos() const;

    void incrementarGol();
    void registrarAmarilla();
    void registrarRoja();
    void registrarFalta();
    void setMinutos(int minutos);
    void actualizarHistorico();

    friend ostream& operator<<(ostream& os, const RegistroJugadorPartido& registro);
};

#endif

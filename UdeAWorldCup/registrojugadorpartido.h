#ifndef REGISTROJUGADORPARTIDO_H
#define REGISTROJUGADORPARTIDO_H

#include <iostream>
#include "Jugador.h"

using namespace std;

class RegistroJugadorPartido
{
private:
    Jugador* jugador;
    int goles;
    int amarillas;
    int rojas;
    int faltas;
    int minutos;

public:
    RegistroJugadorPartido();
    RegistroJugadorPartido(Jugador* jugador);
    RegistroJugadorPartido(const RegistroJugadorPartido& otro);
    ~RegistroJugadorPartido();

    Jugador* getJugador() const;
    int getGoles() const;
    int getAmarillas() const;
    int getRojas() const;
    int getFaltas() const;
    int getMinutos() const;

    void incrementarGol();
    void registrarAmarilla();
    void registrarRoja();
    void registrarFalta();
    void setMinutos(int minutos);

    friend ostream& operator<<(ostream& os, const RegistroJugadorPartido& r);
};

#endif

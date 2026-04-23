#include "RegistroJugadorPartido.h"

RegistroJugadorPartido::RegistroJugadorPartido()
{
    jugador = nullptr;
    goles = 0;
    amarillas = 0;
    rojas = 0;
    faltas = 0;
    minutos = 0;
}

RegistroJugadorPartido::RegistroJugadorPartido(Jugador* jugador)
{
    this->jugador = jugador;
    goles = 0;
    amarillas = 0;
    rojas = 0;
    faltas = 0;
    minutos = 0;
}

RegistroJugadorPartido::RegistroJugadorPartido(const RegistroJugadorPartido& otro)
{
    jugador = otro.jugador;
    goles = otro.goles;
    amarillas = otro.amarillas;
    rojas = otro.rojas;
    faltas = otro.faltas;
    minutos = otro.minutos;
}

RegistroJugadorPartido::~RegistroJugadorPartido()
{
}

Jugador* RegistroJugadorPartido::getJugador() const
{
    return jugador;
}

int RegistroJugadorPartido::getGoles() const
{
    return goles;
}

int RegistroJugadorPartido::getAmarillas() const
{
    return amarillas;
}

int RegistroJugadorPartido::getRojas() const
{
    return rojas;
}

int RegistroJugadorPartido::getFaltas() const
{
    return faltas;
}

int RegistroJugadorPartido::getMinutos() const
{
    return minutos;
}

void RegistroJugadorPartido::incrementarGol()
{
    goles++;
}

void RegistroJugadorPartido::registrarAmarilla()
{
    amarillas++;
}

void RegistroJugadorPartido::registrarRoja()
{
    rojas++;
}

void RegistroJugadorPartido::registrarFalta()
{
    faltas++;
}

void RegistroJugadorPartido::setMinutos(int minutos)
{
    if (minutos >= 0)
    {
        this->minutos = minutos;
    }
}

ostream& operator<<(ostream& os, const RegistroJugadorPartido& r)
{
    if (r.jugador != nullptr)
    {
        os << "Jugador: " << r.jugador->getNombre()
        << " " << r.jugador->getApellido()
        << " | Camiseta: " << r.jugador->getNumeroCamiseta()
        << " | Goles: " << r.goles
        << " | Amarillas: " << r.amarillas
        << " | Rojas: " << r.rojas
        << " | Faltas: " << r.faltas
        << " | Minutos: " << r.minutos;
    }
    else
    {
        os << "Jugador no asignado"
           << " | Goles: " << r.goles
           << " | Amarillas: " << r.amarillas
           << " | Rojas: " << r.rojas
           << " | Faltas: " << r.faltas
           << " | Minutos: " << r.minutos;
    }

    return os;
}

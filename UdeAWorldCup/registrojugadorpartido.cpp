#include "registrojugadorpartido.h"

using namespace std;

RegistroJugadorPartido::RegistroJugadorPartido()
{
    jugador = 0;
    goles = 0;
    tarjetasAmarillas = 0;
    tarjetasRojas = 0;
    faltas = 0;
    minutosJugados = 0;
}

RegistroJugadorPartido::RegistroJugadorPartido(Jugador* jugador)
{
    this->jugador = jugador;
    goles = 0;
    tarjetasAmarillas = 0;
    tarjetasRojas = 0;
    faltas = 0;
    minutosJugados = 0;
}

RegistroJugadorPartido::RegistroJugadorPartido(const RegistroJugadorPartido& otro)
{
    jugador = otro.jugador;
    goles = otro.goles;
    tarjetasAmarillas = otro.tarjetasAmarillas;
    tarjetasRojas = otro.tarjetasRojas;
    faltas = otro.faltas;
    minutosJugados = otro.minutosJugados;
}

RegistroJugadorPartido::~RegistroJugadorPartido()
{
}

Jugador* RegistroJugadorPartido::getJugador() const { return jugador; }
int RegistroJugadorPartido::getGoles() const { return goles; }
int RegistroJugadorPartido::getTarjetasAmarillas() const { return tarjetasAmarillas; }
int RegistroJugadorPartido::getAmarillas() const { return tarjetasAmarillas; }
int RegistroJugadorPartido::getTarjetasRojas() const { return tarjetasRojas; }
int RegistroJugadorPartido::getRojas() const { return tarjetasRojas; }
int RegistroJugadorPartido::getFaltas() const { return faltas; }
int RegistroJugadorPartido::getMinutosJugados() const { return minutosJugados; }
int RegistroJugadorPartido::getMinutos() const { return minutosJugados; }

void RegistroJugadorPartido::incrementarGol() { goles++; }
void RegistroJugadorPartido::registrarAmarilla() { tarjetasAmarillas++; }
void RegistroJugadorPartido::registrarRoja() { tarjetasRojas++; }
void RegistroJugadorPartido::registrarFalta() { faltas++; }

void RegistroJugadorPartido::setMinutos(int minutos)
{
    if (minutos >= 0)
    {
        minutosJugados = minutos;
    }
}

void RegistroJugadorPartido::actualizarHistorico()
{
    if (jugador != 0)
    {
        jugador->actualizarEstadisticas(goles, tarjetasAmarillas, tarjetasRojas, faltas, minutosJugados);
    }
}

ostream& operator<<(ostream& os, const RegistroJugadorPartido& registro)
{
    if (registro.jugador != 0)
    {
        os << registro.jugador->getNombre() << " " << registro.jugador->getApellido()
           << " (#" << registro.jugador->getNumeroCamiseta() << ")";
    }
    else
    {
        os << "Jugador no asignado";
    }

    os << " | Goles: " << registro.goles
       << " | TA: " << registro.tarjetasAmarillas
       << " | TR: " << registro.tarjetasRojas
       << " | Faltas: " << registro.faltas
       << " | Min: " << registro.minutosJugados;
    return os;
}

#include "registrojugadorpartido.h"

RegistroJugadorPartido::RegistroJugadorPartido()
{
    jugador = nullptr;
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

Jugador* RegistroJugadorPartido::getJugador() const
{
    return jugador;
}

int RegistroJugadorPartido::getGoles() const
{
    return goles;
}

int RegistroJugadorPartido::getTarjetasAmarillas() const
{
    return tarjetasAmarillas;
}

int RegistroJugadorPartido::getAmarillas() const
{
    return tarjetasAmarillas;
}

int RegistroJugadorPartido::getTarjetasRojas() const
{
    return tarjetasRojas;
}

int RegistroJugadorPartido::getRojas() const
{
    return tarjetasRojas;
}

int RegistroJugadorPartido::getFaltas() const
{
    return faltas;
}

int RegistroJugadorPartido::getMinutosJugados() const
{
    return minutosJugados;
}

int RegistroJugadorPartido::getMinutos() const
{
    return minutosJugados;
}

void RegistroJugadorPartido::incrementarGol()
{
    goles++;
}

void RegistroJugadorPartido::registrarAmarilla()
{
    tarjetasAmarillas++;
}

void RegistroJugadorPartido::registrarRoja()
{
    tarjetasRojas++;
}

void RegistroJugadorPartido::registrarFalta()
{
    faltas++;
}

void RegistroJugadorPartido::setMinutos(int minutos)
{
    if (minutos >= 0)
    {
        minutosJugados = minutos;
    }
}

void RegistroJugadorPartido::actualizarHistorico()
{
    // El registro del partido transfiere sus datos al histórico del jugador asociado.
    if (jugador != nullptr)
    {
        jugador->actualizarEstadisticas(goles, tarjetasAmarillas, tarjetasRojas, faltas, minutosJugados);
    }
}

std::ostream& operator<<(std::ostream& os, const RegistroJugadorPartido& r)
{
    if (r.jugador != nullptr)
    {
        os << "Jugador: " << r.jugador->getNombre()
        << " " << r.jugador->getApellido()
        << " | Camiseta: " << r.jugador->getNumeroCamiseta()
        << " | Goles: " << r.goles
        << " | Amarillas: " << r.tarjetasAmarillas
        << " | Rojas: " << r.tarjetasRojas
        << " | Faltas: " << r.faltas
        << " | Minutos: " << r.minutosJugados;
    }
    else
    {
        os << "Jugador no asignado"
           << " | Goles: " << r.goles
           << " | Amarillas: " << r.tarjetasAmarillas
           << " | Rojas: " << r.tarjetasRojas
           << " | Faltas: " << r.faltas
           << " | Minutos: " << r.minutosJugados;
    }

    return os;
}

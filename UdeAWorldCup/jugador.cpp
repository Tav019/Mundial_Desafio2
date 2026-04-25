#include "jugador.h"

Jugador::Jugador()
{
    nombre = "";
    apellido = "";
    numeroCamiseta = 0;
    partidosJugados = 0;
    goles = 0;
    minutosJugados = 0;
    asistencias = 0;
    tarjetasAmarillas = 0;
    tarjetasRojas = 0;
    faltas = 0;
}

Jugador::Jugador(const std::string& nombre, const std::string& apellido, int numero)
{
    this->nombre = nombre;
    this->apellido = apellido;
    numeroCamiseta = numero;
    partidosJugados = 0;
    goles = 0;
    minutosJugados = 0;
    asistencias = 0;
    tarjetasAmarillas = 0;
    tarjetasRojas = 0;
    faltas = 0;
}

Jugador::Jugador(const Jugador& otro)
{
    nombre = otro.nombre;
    apellido = otro.apellido;
    numeroCamiseta = otro.numeroCamiseta;
    partidosJugados = otro.partidosJugados;
    goles = otro.goles;
    minutosJugados = otro.minutosJugados;
    asistencias = otro.asistencias;
    tarjetasAmarillas = otro.tarjetasAmarillas;
    tarjetasRojas = otro.tarjetasRojas;
    faltas = otro.faltas;
}

Jugador::~Jugador()
{
}

std::string Jugador::getNombre() const
{
    return nombre;
}

std::string Jugador::getApellido() const
{
    return apellido;
}

int Jugador::getNumeroCamiseta() const
{
    return numeroCamiseta;
}

int Jugador::getPartidosJugados() const
{
    return partidosJugados;
}

int Jugador::getGoles() const
{
    return goles;
}

int Jugador::getMinutosJugados() const
{
    return minutosJugados;
}

int Jugador::getMinutos() const
{
    return minutosJugados;
}

int Jugador::getAsistencias() const
{
    return asistencias;
}

int Jugador::getTarjetasAmarillas() const
{
    return tarjetasAmarillas;
}

int Jugador::getAmarillas() const
{
    return tarjetasAmarillas;
}

int Jugador::getTarjetasRojas() const
{
    return tarjetasRojas;
}

int Jugador::getRojas() const
{
    return tarjetasRojas;
}

int Jugador::getFaltas() const
{
    return faltas;
}

void Jugador::setGoles(int golesIniciales)
{
    if (golesIniciales >= 0)
    {
        goles = golesIniciales;
    }
}

void Jugador::actualizarEstadisticas(int goles, int amarillas, int rojas, int faltas, int minutos)
{
    // Este método resume la actualización histórica del jugador después de un partido.
    if (minutos > 0)
    {
        partidosJugados++;
        minutosJugados += minutos;
    }

    if (goles > 0)
    {
        this->goles += goles;
    }

    if (amarillas > 0)
    {
        tarjetasAmarillas += amarillas;
    }

    if (rojas > 0)
    {
        tarjetasRojas += rojas;
    }

    if (faltas > 0)
    {
        this->faltas += faltas;
    }
}

void Jugador::registrarPartido(int minutos)
{
    actualizarEstadisticas(0, 0, 0, 0, minutos);
}

void Jugador::sumarGol()
{
    goles++;
}

void Jugador::sumarAsistencia()
{
    asistencias++;
}

void Jugador::sumarAmarilla()
{
    tarjetasAmarillas++;
}

void Jugador::sumarRoja()
{
    tarjetasRojas++;
}

void Jugador::sumarFalta()
{
    faltas++;
}

bool Jugador::operator<(const Jugador& otro) const
{
    // Se priorizan los goles para facilitar ordenamientos simples de goleadores.
    if (goles != otro.goles)
    {
        return goles < otro.goles;
    }

    return numeroCamiseta < otro.numeroCamiseta;
}

bool Jugador::operator==(const Jugador& otro) const
{
    return nombre == otro.nombre &&
           apellido == otro.apellido &&
           numeroCamiseta == otro.numeroCamiseta;
}

std::ostream& operator<<(std::ostream& os, const Jugador& jugador)
{
    os << jugador.nombre << " " << jugador.apellido
       << " | #" << jugador.numeroCamiseta
       << " | PJ: " << jugador.partidosJugados
       << " | Goles: " << jugador.goles
       << " | Min: " << jugador.minutosJugados
       << " | A: " << jugador.asistencias
       << " | TA: " << jugador.tarjetasAmarillas
       << " | TR: " << jugador.tarjetasRojas
       << " | F: " << jugador.faltas;

    return os;
}

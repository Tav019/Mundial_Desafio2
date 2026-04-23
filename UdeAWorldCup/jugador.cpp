#include "Jugador.h"

Jugador::Jugador()
{
    nombre = "";
    apellido = "";
    numeroCamiseta = 0;

    partidosJugados = 0;
    goles = 0;
    minutos = 0;
    asistencias = 0;
    amarillas = 0;
    rojas = 0;
    faltas = 0;
}

Jugador::Jugador(const string& nombre, const string& apellido, int numeroCamiseta)
{
    this->nombre = nombre;
    this->apellido = apellido;
    this->numeroCamiseta = numeroCamiseta;

    partidosJugados = 0;
    goles = 0;
    minutos = 0;
    asistencias = 0;
    amarillas = 0;
    rojas = 0;
    faltas = 0;
}

Jugador::Jugador(const Jugador& otro)
{
    nombre = otro.nombre;
    apellido = otro.apellido;
    numeroCamiseta = otro.numeroCamiseta;

    partidosJugados = otro.partidosJugados;
    goles = otro.goles;
    minutos = otro.minutos;
    asistencias = otro.asistencias;
    amarillas = otro.amarillas;
    rojas = otro.rojas;
    faltas = otro.faltas;
}

Jugador::~Jugador()
{
}

string Jugador::getNombre() const
{
    return nombre;
}

string Jugador::getApellido() const
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

int Jugador::getMinutos() const
{
    return minutos;
}

int Jugador::getAsistencias() const
{
    return asistencias;
}

int Jugador::getAmarillas() const
{
    return amarillas;
}

int Jugador::getRojas() const
{
    return rojas;
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

void Jugador::registrarPartido(int minutosJugados)
{
    if (minutosJugados > 0)
    {
        partidosJugados++;
        minutos += minutosJugados;
    }
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
    amarillas++;
}

void Jugador::sumarRoja()
{
    rojas++;
}

void Jugador::sumarFalta()
{
    faltas++;
}

bool Jugador::operator==(const Jugador& otro) const
{
    return nombre == otro.nombre &&
           apellido == otro.apellido &&
           numeroCamiseta == otro.numeroCamiseta;
}

ostream& operator<<(ostream& os, const Jugador& j)
{
    os << "Nombre: " << j.nombre
       << " " << j.apellido
       << " | Camiseta: " << j.numeroCamiseta
       << " | PJ: " << j.partidosJugados
       << " | Goles: " << j.goles
       << " | Minutos: " << j.minutos
       << " | Asistencias: " << j.asistencias
       << " | Amarillas: " << j.amarillas
       << " | Rojas: " << j.rojas
       << " | Faltas: " << j.faltas;

    return os;
}

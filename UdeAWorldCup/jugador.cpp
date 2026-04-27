#include "jugador.h"

using namespace std;

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

Jugador::Jugador(const string& _nombre, const string& _apellido, int _numeroCamiseta)
{
    nombre = _nombre;
    apellido = _apellido;
    numeroCamiseta = _numeroCamiseta;
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

string Jugador::getNombre() const { return nombre; }
string Jugador::getApellido() const { return apellido; }
int Jugador::getNumeroCamiseta() const { return numeroCamiseta; }
int Jugador::getPartidosJugados() const { return partidosJugados; }
int Jugador::getGoles() const { return goles; }
int Jugador::getMinutosJugados() const { return minutosJugados; }
int Jugador::getMinutos() const { return minutosJugados; }
int Jugador::getAsistencias() const { return asistencias; }
int Jugador::getTarjetasAmarillas() const { return tarjetasAmarillas; }
int Jugador::getAmarillas() const { return tarjetasAmarillas; }
int Jugador::getTarjetasRojas() const { return tarjetasRojas; }
int Jugador::getRojas() const { return tarjetasRojas; }
int Jugador::getFaltas() const { return faltas; }

void Jugador::setGoles(int golesIniciales)
{
    if (golesIniciales >= 0)
    {
        goles = golesIniciales;
    }
}

void Jugador::actualizarEstadisticas(int _goles, int amarillas, int rojas, int _faltas, int minutos)
{
    if (minutos > 0)
    {
        partidosJugados++;
        minutosJugados += minutos;
    }

    if (_goles > 0) goles += _goles;
    if (amarillas > 0) tarjetasAmarillas += amarillas;
    if (rojas > 0) tarjetasRojas += rojas;
    if (_faltas > 0) faltas += _faltas;
}

void Jugador::registrarPartido(int minutos)
{
    actualizarEstadisticas(0, 0, 0, 0, minutos);
}

void Jugador::sumarGol() { goles++; }
void Jugador::sumarAsistencia() { asistencias++; }
void Jugador::sumarAmarilla() { tarjetasAmarillas++; }
void Jugador::sumarRoja() { tarjetasRojas++; }
void Jugador::sumarFalta() { faltas++; }

bool Jugador::operator<(const Jugador& otro) const
{
    if (goles != otro.goles) return goles < otro.goles;
    if (asistencias != otro.asistencias) return asistencias < otro.asistencias;
    return numeroCamiseta > otro.numeroCamiseta;
}

bool Jugador::operator==(const Jugador& otro) const
{
    return nombre == otro.nombre && apellido == otro.apellido && numeroCamiseta == otro.numeroCamiseta;
}

ostream& operator<<(ostream& os, const Jugador& jugador)
{
    os << jugador.nombre << " " << jugador.apellido
       << " | #" << jugador.numeroCamiseta
       << " | PJ: " << jugador.partidosJugados
       << " | Goles: " << jugador.goles
       << " | Min: " << jugador.minutosJugados
       << " | Asist: " << jugador.asistencias
       << " | TA: " << jugador.tarjetasAmarillas
       << " | TR: " << jugador.tarjetasRojas
       << " | Faltas: " << jugador.faltas;
    return os;
}

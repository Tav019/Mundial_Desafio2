#ifndef JUGADOR_H
#define JUGADOR_H

#include <iostream>
#include <string>

using namespace std;

class Jugador
{
private:
    string nombre;
    string apellido;
    int numeroCamiseta;
    int partidosJugados;
    int goles;
    int minutosJugados;
    int asistencias;
    int tarjetasAmarillas;
    int tarjetasRojas;
    int faltas;

public:
    Jugador();
    Jugador(const string& nombre, const string& apellido, int numeroCamiseta);
    Jugador(const Jugador& otro);
    ~Jugador();

    string getNombre() const;
    string getApellido() const;
    int getNumeroCamiseta() const;
    int getPartidosJugados() const;
    int getGoles() const;
    int getMinutosJugados() const;
    int getMinutos() const;
    int getAsistencias() const;
    int getTarjetasAmarillas() const;
    int getAmarillas() const;
    int getTarjetasRojas() const;
    int getRojas() const;
    int getFaltas() const;

    void setGoles(int golesIniciales);
    void actualizarEstadisticas(int goles, int amarillas, int rojas, int faltas, int minutos);
    void registrarPartido(int minutos);
    void sumarGol();
    void sumarAsistencia();
    void sumarAmarilla();
    void sumarRoja();
    void sumarFalta();

    bool operator<(const Jugador& otro) const;
    bool operator==(const Jugador& otro) const;

    friend ostream& operator<<(ostream& os, const Jugador& jugador);
};

#endif

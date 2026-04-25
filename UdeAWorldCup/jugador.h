#ifndef JUGADOR_H
#define JUGADOR_H

#include <iostream>
#include <string>

class Jugador
{
private:
    std::string nombre;
    std::string apellido;
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
    Jugador(const std::string& nombre, const std::string& apellido, int numero);
    Jugador(const Jugador& otro);
    ~Jugador();

    std::string getNombre() const;
    std::string getApellido() const;
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

    friend std::ostream& operator<<(std::ostream& os, const Jugador& jugador);
};

#endif

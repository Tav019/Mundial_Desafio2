#ifndef ESTADISTICAJUGADOR_H
#define ESTADISTICAJUGADOR_H

#include <iostream>

class EstadisticaJugador {
private:
    int partidosJugados;
    int goles;
    int minutos;
    int asistencias;
    int amarillas;
    int rojas;
    int faltas;

public:
    EstadisticaJugador();

    int getPartidosJugados() const;
    int getGoles() const;
    int getMinutos() const;
    int getAsistencias() const;
    int getAmarillas() const;
    int getRojas() const;
    int getFaltas() const;

    void registrarPartido(int minutosJugados);
    void sumarGol();
    void sumarAsistencia();
    void sumarAmarilla();
    void sumarRoja();
    void sumarFalta();
    void sumarMinutos(int minutosExtra);

    friend std::ostream& operator<<(std::ostream& os, const EstadisticaJugador& e);
};

#endif

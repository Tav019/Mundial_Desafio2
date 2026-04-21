#include "EstadisticaJugador.h"

EstadisticaJugador::EstadisticaJugador()
    : partidosJugados(0),
    goles(0),
    minutos(0),
    asistencias(0),
    amarillas(0),
    rojas(0),
    faltas(0) {
}

int EstadisticaJugador::getPartidosJugados() const {
    return partidosJugados;
}

int EstadisticaJugador::getGoles() const {
    return goles;
}

int EstadisticaJugador::getMinutos() const {
    return minutos;
}

int EstadisticaJugador::getAsistencias() const {
    return asistencias;
}

int EstadisticaJugador::getAmarillas() const {
    return amarillas;
}

int EstadisticaJugador::getRojas() const {
    return rojas;
}

int EstadisticaJugador::getFaltas() const {
    return faltas;
}

void EstadisticaJugador::registrarPartido(int minutosJugados) {
    if (minutosJugados >= 0) {
        partidosJugados++;
        minutos += minutosJugados;
    }
}

void EstadisticaJugador::sumarGol() {
    goles++;
}

void EstadisticaJugador::sumarAsistencia() {
    asistencias++;
}

void EstadisticaJugador::sumarAmarilla() {
    amarillas++;
}

void EstadisticaJugador::sumarRoja() {
    rojas++;
}

void EstadisticaJugador::sumarFalta() {
    faltas++;
}

void EstadisticaJugador::sumarMinutos(int minutosExtra) {
    if (minutosExtra > 0) {
        minutos += minutosExtra;
    }
}

std::ostream& operator<<(std::ostream& os, const EstadisticaJugador& e) {
    os << "PJ: " << e.partidosJugados
       << " | Goles: " << e.goles
       << " | Min: " << e.minutos
       << " | Asist: " << e.asistencias
       << " | Amarillas: " << e.amarillas
       << " | Rojas: " << e.rojas
       << " | Faltas: " << e.faltas;
    return os;
}

#ifndef PARTIDO_H
#define PARTIDO_H

#include <iostream>
#include <string>

using namespace std;

#include "Lista.h"
#include "equipo.h"
#include "fecha.h"
#include "registrojugadorpartido.h"

class Partido
{
private:
    Fecha fecha;
    string hora;
    string sede;
    string arbitro1;
    string arbitro2;
    string arbitro3;
    Equipo* equipo1;
    Equipo* equipo2;
    int golesEquipo1;
    int golesEquipo2;
    float posesionEquipo1;
    float posesionEquipo2;
    bool prorroga;
    string etapa;
    bool simulado;
    Lista<RegistroJugadorPartido*> convocadosEquipo1;
    Lista<RegistroJugadorPartido*> convocadosEquipo2;

    int calcularGolesEsperados(Equipo* atacante, Equipo* defensor) const;
    void asignarEventosJugadores(Lista<RegistroJugadorPartido*>& convocados, int golesDelEquipo, int minutosBase);
    int sumarTarjetas(const Lista<RegistroJugadorPartido*>& convocados) const;
    int sumarRojas(const Lista<RegistroJugadorPartido*>& convocados) const;
    int sumarFaltas(const Lista<RegistroJugadorPartido*>& convocados) const;
    void liberarConvocados();

public:
    Partido();
    Partido(Equipo* equipo1, Equipo* equipo2, const Fecha& fecha, const string& etapa);
    ~Partido();

    void configurar(const string& sede, const string& hora);
    void setArbitros(const string& arbitro1, const string& arbitro2, const string& arbitro3);
    void seleccionarConvocados();
    void calcularPosesion();
    void simularGoles();
    void simularTarjetasYFaltas();
    void resolverEmpate();
    void actualizarHistoricos();
    void simular();

    Equipo* getEquipo1() const;
    Equipo* getEquipo2() const;
    int getGolesEquipo1() const;
    int getGolesEquipo2() const;
    float getPosesionEquipo1() const;
    float getPosesionEquipo2() const;
    Equipo* getGanador() const;
    Equipo* getPerdedor() const;
    bool huboProrroga() const;
    bool fueSimulado() const;
    Fecha getFecha() const;
    string getEtapa() const;
    const Lista<RegistroJugadorPartido*>& getConvocadosEquipo1() const;
    const Lista<RegistroJugadorPartido*>& getConvocadosEquipo2() const;

    friend ostream& operator<<(ostream& os, const Partido& partido);
};

#endif

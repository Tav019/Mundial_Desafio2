#ifndef PARTIDO_H
#define PARTIDO_H

#include <iostream>
#include <string>

#include "Lista.h"
#include "equipo.h"
#include "fecha.h"
#include "registrojugadorpartido.h"

class Partido
{
private:
    Fecha fecha;
    std::string hora;
    std::string sede;
    std::string arbitro1;
    std::string arbitro2;
    std::string arbitro3;
    Equipo* equipo1;
    Equipo* equipo2;
    int golesEquipo1;
    int golesEquipo2;
    float posesionEquipo1;
    float posesionEquipo2;
    bool prorroga;
    std::string etapa;
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
    Partido(Equipo* equipo1, Equipo* equipo2, const Fecha& fecha, const std::string& etapa);
    ~Partido();

    void configurar(const std::string& sede, const std::string& hora);
    void setArbitros(const std::string& arbitro1, const std::string& arbitro2, const std::string& arbitro3);
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
    Equipo* getGanador() const;
    bool huboProrroga() const;
    Fecha getFecha() const;
    std::string getEtapa() const;
    const Lista<RegistroJugadorPartido*>& getConvocadosEquipo1() const;
    const Lista<RegistroJugadorPartido*>& getConvocadosEquipo2() const;

    friend std::ostream& operator<<(std::ostream& os, const Partido& partido);
};

#endif

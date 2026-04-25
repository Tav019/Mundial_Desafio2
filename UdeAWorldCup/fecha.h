#ifndef FECHA_H
#define FECHA_H

#include <iostream>

class Fecha
{
private:
    int dia;
    int mes;
    int anio;

    bool esBisiesto(int anio) const;
    int diasDelMes(int mes, int anio) const;
    bool esValidaInterna(int dia, int mes, int anio) const;
    int convertirADias() const;

public:
    Fecha();
    Fecha(int dia, int mes, int anio);
    ~Fecha();

    void avanzarDias(int dias);
    int diferencia(const Fecha& otra) const;
    bool esValida() const;

    int getDia() const;
    int getMes() const;
    int getAnio() const;

    bool operator==(const Fecha& otra) const;
    bool operator<(const Fecha& otra) const;

    friend std::ostream& operator<<(std::ostream& os, const Fecha& fecha);
};

#endif

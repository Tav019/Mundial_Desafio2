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
    int diasMes(int mes, int anio) const;
    bool validacion(int dia, int mes, int anio) const;
    int convDias() const;


public:
    Fecha();
    Fecha(int dia, int mes, int anio);

    int getDia() const;
    int getMes() const;
    int getAnio() const;

    int diferencia(const Fecha& otra) const;
    Fecha avanzar(int n) const;

    bool operator==(const Fecha& otra) const;
    bool operator<(const Fecha& otra) const;

    int dias2026() const;

    friend std::ostream& operator <<(std::ostream& os, const Fecha& f);
};

#endif // FECHA_H

#include "fecha.h"

using namespace std;

Fecha::Fecha()
{
    dia = 1;
    mes = 1;
    anio = 2026;
}

Fecha::Fecha(int dia, int mes, int anio)
{
    if (esValidaInterna(dia, mes, anio))
    {
        this->dia = dia;
        this->mes = mes;
        this->anio = anio;
    }
    else
    {
        this->dia = 1;
        this->mes = 1;
        this->anio = 2026;
    }
}

Fecha::~Fecha()
{
}

bool Fecha::esBisiesto(int anio) const
{
    return (anio % 400 == 0) || (anio % 4 == 0 && anio % 100 != 0);
}

int Fecha::diasDelMes(int mes, int anio) const
{
    if (mes == 2) return esBisiesto(anio) ? 29 : 28;
    if (mes == 4 || mes == 6 || mes == 9 || mes == 11) return 30;
    return 31;
}

bool Fecha::esValidaInterna(int dia, int mes, int anio) const
{
    if (anio < 1 || mes < 1 || mes > 12 || dia < 1) return false;
    return dia <= diasDelMes(mes, anio);
}

int Fecha::convertirADias() const
{
    int total = 0;

    for (int a = 1; a < anio; a++)
    {
        total += esBisiesto(a) ? 366 : 365;
    }

    for (int m = 1; m < mes; m++)
    {
        total += diasDelMes(m, anio);
    }

    total += dia;
    return total;
}

void Fecha::avanzarDias(int dias)
{
    if (dias < 0) return;

    while (dias > 0)
    {
        dia++;
        if (dia > diasDelMes(mes, anio))
        {
            dia = 1;
            mes++;
            if (mes > 12)
            {
                mes = 1;
                anio++;
            }
        }
        dias--;
    }
}

int Fecha::diferencia(const Fecha& otra) const
{
    int dif = otra.convertirADias() - convertirADias();
    return dif < 0 ? -dif : dif;
}

bool Fecha::esValida() const
{
    return esValidaInterna(dia, mes, anio);
}

int Fecha::getDia() const { return dia; }
int Fecha::getMes() const { return mes; }
int Fecha::getAnio() const { return anio; }

bool Fecha::operator==(const Fecha& otra) const
{
    return dia == otra.dia && mes == otra.mes && anio == otra.anio;
}

bool Fecha::operator<(const Fecha& otra) const
{
    return convertirADias() < otra.convertirADias();
}

ostream& operator<<(ostream& os, const Fecha& fecha)
{
    if (fecha.dia < 10) os << "0";
    os << fecha.dia << "/";
    if (fecha.mes < 10) os << "0";
    os << fecha.mes << "/" << fecha.anio;
    return os;
}

#include "fecha.h"

Fecha::Fecha()
{
    dia = 1;
    mes = 1;
    anio = 2000;
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
        this->anio = 2000;
    }
}

Fecha::~Fecha()
{
}

bool Fecha::esBisiesto(int anio) const
{
    if (anio % 400 == 0) return true;
    if (anio % 100 == 0) return false;
    return anio % 4 == 0;
}

int Fecha::diasDelMes(int mes, int anio) const
{
    switch (mes)
    {
        case 1: return 31;
        case 2: return esBisiesto(anio) ? 29 : 28;
        case 3: return 31;
        case 4: return 30;
        case 5: return 31;
        case 6: return 30;
        case 7: return 31;
        case 8: return 31;
        case 9: return 30;
        case 10: return 31;
        case 11: return 30;
        case 12: return 31;
        default: return 0;
    }
}

bool Fecha::esValidaInterna(int dia, int mes, int anio) const
{
    if (anio < 0 || mes < 1 || mes > 12)
    {
        return false;
    }

    return dia >= 1 && dia <= diasDelMes(mes, anio);
}

int Fecha::convertirADias() const
{
    // Se transforma la fecha a un total absoluto de días para comparar y restar fechas.
    int total = 0;

    for (int a = 0; a < anio; a++)
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
    for (int i = 0; i < dias; i++)
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
    }
}

int Fecha::diferencia(const Fecha& otra) const
{
    return convertirADias() - otra.convertirADias();
}

bool Fecha::esValida() const
{
    return esValidaInterna(dia, mes, anio);
}

int Fecha::getDia() const
{
    return dia;
}

int Fecha::getMes() const
{
    return mes;
}

int Fecha::getAnio() const
{
    return anio;
}

bool Fecha::operator==(const Fecha& otra) const
{
    return dia == otra.dia && mes == otra.mes && anio == otra.anio;
}

bool Fecha::operator<(const Fecha& otra) const
{
    if (anio != otra.anio) return anio < otra.anio;
    if (mes != otra.mes) return mes < otra.mes;
    return dia < otra.dia;
}

std::ostream& operator<<(std::ostream& os, const Fecha& fecha)
{
    os << fecha.dia << "/" << fecha.mes << "/" << fecha.anio;
    return os;
}












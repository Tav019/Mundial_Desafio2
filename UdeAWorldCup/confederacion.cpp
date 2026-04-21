#include "Confederacion.h"

Confederacion::Confederacion()
    : nombre(""), codigo("")
{
}

Confederacion::Confederacion(const string& nombre, const string& codigo)
    : nombre(nombre), codigo(codigo)
{
}

string Confederacion::getNombre() const
{
    return nombre;
}

string Confederacion::getCodigo() const
{
    return codigo;
}

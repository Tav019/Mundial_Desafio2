#include "recursos.h"

using namespace std;

Recursos::Recursos()
{
    iteraciones = 0;
    bytes = 0;
}

Recursos::Recursos(long _iteraciones, long _bytes)
{
    iteraciones = _iteraciones >= 0 ? _iteraciones : 0;
    bytes = _bytes >= 0 ? _bytes : 0;
}

Recursos::~Recursos()
{
}

void Recursos::contarIteracion()
{
    iteraciones++;
}

void Recursos::contarIteraciones(long cantidad)
{
    if (cantidad > 0)
    {
        iteraciones += cantidad;
    }
}

void Recursos::contarBytes(long cantidad)
{
    if (cantidad > 0)
    {
        bytes += cantidad;
    }
}

void Recursos::liberarBytes(long cantidad)
{
    if (cantidad > 0)
    {
        bytes -= cantidad;
        if (bytes < 0) bytes = 0;
    }
}

void Recursos::setBytes(long _bytes)
{
    bytes = _bytes >= 0 ? _bytes : 0;
}

void Recursos::reiniciar()
{
    iteraciones = 0;
    bytes = 0;
}

long Recursos::getIteraciones() const { return iteraciones; }
long Recursos::getBytes() const { return bytes; }

ostream& operator<<(ostream& os, const Recursos& recursos)
{
    os << "Iteraciones estimadas: " << recursos.iteraciones
       << " | Memoria estimada: " << recursos.bytes << " bytes";
    return os;
}

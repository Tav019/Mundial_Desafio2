#include "recursos.h"

Recursos::Recursos()
{
    iteraciones = 0;
    bytes = 0;
}

Recursos::Recursos(long iteraciones, long bytes)
{
    this->iteraciones = iteraciones >= 0 ? iteraciones : 0;
    this->bytes = bytes >= 0 ? bytes : 0;
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
        if (bytes < 0)
        {
            bytes = 0;
        }
    }
}

void Recursos::reiniciar()
{
    iteraciones = 0;
    bytes = 0;
}

long Recursos::getIteraciones() const
{
    return iteraciones;
}

long Recursos::getBytes() const
{
    return bytes;
}

std::ostream& operator<<(std::ostream& os, const Recursos& recursos)
{
    os << "Iteraciones: " << recursos.iteraciones
       << " | Bytes estimados: " << recursos.bytes;
    return os;
}

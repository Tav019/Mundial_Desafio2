#ifndef RECURSOS_H
#define RECURSOS_H

#include <iostream>

class Recursos
{
private:
    long iteraciones;
    long bytes;

public:
    Recursos();
    Recursos(long iteraciones, long bytes);
    ~Recursos();

    void contarIteracion();
    void contarIteraciones(long cantidad);
    void contarBytes(long cantidad);
    void liberarBytes(long cantidad);
    void reiniciar();

    long getIteraciones() const;
    long getBytes() const;

    friend std::ostream& operator<<(std::ostream& os, const Recursos& recursos);
};

#endif

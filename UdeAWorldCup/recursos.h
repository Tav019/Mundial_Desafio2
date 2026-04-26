#ifndef RECURSOS_H
#define RECURSOS_H

#include <iostream>

using namespace std;

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
    void setBytes(long bytes);
    void reiniciar();

    long getIteraciones() const;
    long getBytes() const;

    friend ostream& operator<<(ostream& os, const Recursos& recursos);
};

#endif

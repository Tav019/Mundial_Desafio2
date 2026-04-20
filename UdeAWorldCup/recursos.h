#ifndef RECURSOS_H
#define RECURSOS_H

#include <iostream>

class Recursos
{
private:
    long iteraciones;
    long bytes;
     bool validacion(long interaciones, long bytes);

public:
    Recursos();
    Recursos(long iteraciones, long bytes);

    void contarIteraciones(long iteraciones = 1);
    void contarBytes(long bytes);
    void liberarBytes(long bytes);

    void reiniciar();

    long getIteraciones();
    long getBytes();



    friend std::ostream& operator <<(std::ostream& os, const Recursos& r);

};

#endif // RECURSOS_H

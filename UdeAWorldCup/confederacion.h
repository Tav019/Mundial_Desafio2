#ifndef CONFEDERACION_H
#define CONFEDERACION_H

#include <string>
using namespace std;

class Confederacion {
private:
    string nombre;
    string codigo;

public:
    Confederacion();
    Confederacion(const string& nombre, const string& codigo);

    string getNombre() const;
    string getCodigo() const;
};

#endif

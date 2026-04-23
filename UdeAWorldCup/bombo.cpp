#include "Bombo.h"
#include "Equipo.h"
#include <cstdlib>

Bombo::Bombo()
{
    numero = 0;
}

Bombo::Bombo(int numero)
{
    this->numero = numero;
}

Bombo::Bombo(const Bombo& otro)
{
    numero = otro.numero;
    equipos = otro.equipos;
}

Bombo::~Bombo()
{
}

int Bombo::getNumero() const
{
    return numero;
}

int Bombo::getTamano() const
{
    return equipos.getTamano();
}

bool Bombo::vacio() const
{
    return equipos.vacia();
}

void Bombo::agregar(Equipo* equipo)
{
    if (equipo == nullptr)
    {
        return;
    }

    for (int i = 0; i < equipos.getTamano(); i++)
    {
        if (equipos[i] == equipo)
        {
            return;
        }
    }

    equipos.agregar(equipo);
}

Equipo* Bombo::extraerAleatorio()
{
    if (vacio())
    {
        return nullptr;
    }

    int indice = rand() % equipos.getTamano();
    Equipo* seleccionado = equipos[indice];
    equipos.eliminar(indice);

    return seleccionado;
}

void Bombo::devolver(Equipo* equipo)
{
    agregar(equipo);
}

ostream& operator<<(ostream& os, const Bombo& b)
{
    os << "Bombo " << b.numero << endl;
    os << "Equipos:" << endl;

    for (int i = 0; i < b.equipos.getTamano(); i++)
    {
        if (b.equipos[i] != nullptr)
        {
            os << "- " << b.equipos[i]->getPais() << endl;
        }
    }

    return os;
}

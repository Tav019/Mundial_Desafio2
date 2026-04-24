#include "Grupo.h"
#include "Equipo.h"
#include "Partido.h"

Grupo::Grupo()
{
    letra = '?';
}

Grupo::Grupo(char letra)
{
    this->letra = letra;
}

Grupo::Grupo(const Grupo& otro)
{
    letra = otro.letra;
    equipos = otro.equipos;
    partidos = otro.partidos;
}

Grupo::~Grupo()
{
}

char Grupo::getLetra() const
{
    return letra;
}

Lista<Equipo*>& Grupo::getEquipos()
{
    return equipos;
}

Lista<Partido*>& Grupo::getPartidos()
{
    return partidos;
}

int Grupo::buscarEquipo(Equipo* equipo) const
{
    for (int i = 0; i < equipos.getTamano(); i++)
    {
        if (equipos[i] == equipo)
        {
            return i;
        }
    }

    return -1;
}

void Grupo::agregarEquipo(Equipo* equipo)
{
    if (equipo == nullptr)
    {
        return;
    }

    if (equipos.getTamano() >= 4)
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

void Grupo::agregarPartido(Partido* partido)
{
    if (partido == nullptr)
    {
        return;
    }

    for (int i = 0; i < partidos.getTamano(); i++)
    {
        if (partidos[i] == partido)
        {
            return;
        }
    }

    partidos.agregar(partido);
}

Lista<Equipo*> Grupo::ordenarEquipos() const
{
    Lista<int> puntos;
    Lista<int> golesFavor;
    Lista<int> golesContra;

    for (int i = 0; i < equipos.getTamano(); i++)
    {
        puntos.agregar(0);
        golesFavor.agregar(0);
        golesContra.agregar(0);
    }

    for (int i = 0; i < partidos.getTamano(); i++)
    {
        Partido* p = partidos[i];

        if (p == nullptr)
        {
            continue;
        }

        Equipo* e1 = p->getEquipo1();
        Equipo* e2 = p->getEquipo2();

        int idx1 = buscarEquipo(e1);
        int idx2 = buscarEquipo(e2);

        if (idx1 == -1 || idx2 == -1)
        {
            continue;
        }

        int g1 = p->getGolesEquipo1();
        int g2 = p->getGolesEquipo2();

        golesFavor[idx1] += g1;
        golesContra[idx1] += g2;

        golesFavor[idx2] += g2;
        golesContra[idx2] += g1;

        if (g1 > g2)
        {
            puntos[idx1] += 3;
        }
        else if (g2 > g1)
        {
            puntos[idx2] += 3;
        }
        else
        {
            puntos[idx1] += 1;
            puntos[idx2] += 1;
        }
    }

    Lista<Equipo*> orden;

    for (int i = 0; i < equipos.getTamano(); i++)
    {
        orden.agregar(equipos[i]);
    }

    for (int i = 0; i < orden.getTamano() - 1; i++)
    {
        for (int j = i + 1; j < orden.getTamano(); j++)
        {
            int idxI = buscarEquipo(orden[i]);
            int idxJ = buscarEquipo(orden[j]);

            int puntosI = puntos[idxI];
            int puntosJ = puntos[idxJ];

            int dgI = golesFavor[idxI] - golesContra[idxI];
            int dgJ = golesFavor[idxJ] - golesContra[idxJ];

            int gfI = golesFavor[idxI];
            int gfJ = golesFavor[idxJ];

            bool intercambiar = false;

            if (puntosJ > puntosI)
            {
                intercambiar = true;
            }
            else if (puntosJ == puntosI)
            {
                if (dgJ > dgI)
                {
                    intercambiar = true;
                }
                else if (dgJ == dgI)
                {
                    if (gfJ > gfI)
                    {
                        intercambiar = true;
                    }
                    else if (gfJ == gfI)
                    {
                        if (orden[j]->getPais() < orden[i]->getPais())
                        {
                            intercambiar = true;
                        }
                    }
                }
            }

            if (intercambiar)
            {
                Equipo* aux = orden[i];
                orden[i] = orden[j];
                orden[j] = aux;
            }
        }
    }

    return orden;
}

Equipo* Grupo::getPrimero() const
{
    Lista<Equipo*> orden = ordenarEquipos();

    if (orden.getTamano() >= 1)
    {
        return orden[0];
    }

    return nullptr;
}

Equipo* Grupo::getSegundo() const
{
    Lista<Equipo*> orden = ordenarEquipos();

    if (orden.getTamano() >= 2)
    {
        return orden[1];
    }

    return nullptr;
}

Equipo* Grupo::getTercero() const
{
    Lista<Equipo*> orden = ordenarEquipos();

    if (orden.getTamano() >= 3)
    {
        return orden[2];
    }

    return nullptr;
}

ostream& operator<<(ostream& os, const Grupo& g)
{
    os << "Grupo " << g.letra << endl;
    os << "Equipos:" << endl;

    for (int i = 0; i < g.equipos.getTamano(); i++)
    {
        if (g.equipos[i] != nullptr)
        {
            os << "- " << g.equipos[i]->getPais() << endl;
        }
    }

    Lista<Equipo*> orden = g.ordenarEquipos();

    os << "Tabla del grupo:" << endl;
    for (int i = 0; i < orden.getTamano(); i++)
    {
        if (orden[i] != nullptr)
        {
            os << i + 1 << ". " << orden[i]->getPais() << endl;
        }
    }

    return os;
}

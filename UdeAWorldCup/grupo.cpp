#include "grupo.h"

using namespace std;

#include <cstdlib>

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
    // Los partidos y equipos son liberados por Torneo.
}

char Grupo::getLetra() const { return letra; }
Lista<Equipo*>& Grupo::getEquipos() { return equipos; }
const Lista<Equipo*>& Grupo::getEquipos() const { return equipos; }
Lista<Partido*>& Grupo::getPartidos() { return partidos; }
const Lista<Partido*>& Grupo::getPartidos() const { return partidos; }

int Grupo::buscarEquipo(Equipo* equipo) const
{
    for (int i = 0; i < equipos.getCantidad(); i++)
    {
        if (equipos[i] == equipo)
        {
            return i;
        }
    }

    return -1;
}

bool Grupo::validarConfederacion(Equipo* equipo) const
{
    if (equipo == 0)
    {
        return false;
    }

    int cantidadMismaConfederacion = 0;

    for (int i = 0; i < equipos.getCantidad(); i++)
    {
        if (equipos[i]->getConfederacion() == equipo->getConfederacion())
        {
            cantidadMismaConfederacion++;
        }
    }

    if (equipo->getConfederacion() == "UEFA")
    {
        return cantidadMismaConfederacion < 2;
    }

    return cantidadMismaConfederacion < 1;
}

bool Grupo::agregarEquipo(Equipo* equipo)
{
    if (equipo == 0 || equipos.getCantidad() >= 4)
    {
        return false;
    }

    for (int i = 0; i < equipos.getCantidad(); i++)
    {
        if (equipos[i] == equipo)
        {
            return false;
        }
    }

    if (!validarConfederacion(equipo))
    {
        return false;
    }

    equipos.agregar(equipo);
    return true;
}

bool Grupo::agregarPartido(Partido* partido)
{
    if (partido == 0)
    {
        return false;
    }

    for (int i = 0; i < partidos.getCantidad(); i++)
    {
        if (partidos[i] == partido)
        {
            return false;
        }
    }

    partidos.agregar(partido);
    return true;
}

void Grupo::simularPartidos()
{
    for (int i = 0; i < partidos.getCantidad(); i++)
    {
        partidos[i]->simular();
    }
}

int Grupo::getPuntosDeEquipo(Equipo* equipo) const
{
    int puntos = 0;

    for (int i = 0; i < partidos.getCantidad(); i++)
    {
        Partido* partido = partidos[i];
        if (partido == 0 || !partido->fueSimulado()) continue;

        Equipo* e1 = partido->getEquipo1();
        Equipo* e2 = partido->getEquipo2();
        int g1 = partido->getGolesEquipo1();
        int g2 = partido->getGolesEquipo2();

        if (e1 == equipo)
        {
            if (g1 > g2) puntos += 3;
            else if (g1 == g2) puntos += 1;
        }
        else if (e2 == equipo)
        {
            if (g2 > g1) puntos += 3;
            else if (g1 == g2) puntos += 1;
        }
    }

    return puntos;
}

int Grupo::getGolesFavorGrupo(Equipo* equipo) const
{
    int goles = 0;

    for (int i = 0; i < partidos.getCantidad(); i++)
    {
        Partido* partido = partidos[i];
        if (partido == 0 || !partido->fueSimulado()) continue;

        if (partido->getEquipo1() == equipo) goles += partido->getGolesEquipo1();
        else if (partido->getEquipo2() == equipo) goles += partido->getGolesEquipo2();
    }

    return goles;
}

int Grupo::getGolesContraGrupo(Equipo* equipo) const
{
    int goles = 0;

    for (int i = 0; i < partidos.getCantidad(); i++)
    {
        Partido* partido = partidos[i];
        if (partido == 0 || !partido->fueSimulado()) continue;

        if (partido->getEquipo1() == equipo) goles += partido->getGolesEquipo2();
        else if (partido->getEquipo2() == equipo) goles += partido->getGolesEquipo1();
    }

    return goles;
}

int Grupo::getDiferenciaGolGrupo(Equipo* equipo) const
{
    return getGolesFavorGrupo(equipo) - getGolesContraGrupo(equipo);
}

Lista<Equipo*> Grupo::ordenarEquipos() const
{
    Lista<Equipo*> orden;

    for (int i = 0; i < equipos.getCantidad(); i++)
    {
        orden.agregar(equipos[i]);
    }

    for (int i = 0; i < orden.getCantidad() - 1; i++)
    {
        for (int j = i + 1; j < orden.getCantidad(); j++)
        {
            int puntosI = getPuntosDeEquipo(orden[i]);
            int puntosJ = getPuntosDeEquipo(orden[j]);
            int dgI = getDiferenciaGolGrupo(orden[i]);
            int dgJ = getDiferenciaGolGrupo(orden[j]);
            int gfI = getGolesFavorGrupo(orden[i]);
            int gfJ = getGolesFavorGrupo(orden[j]);

            bool intercambiar = false;

            if (puntosJ > puntosI) intercambiar = true;
            else if (puntosJ == puntosI)
            {
                if (dgJ > dgI) intercambiar = true;
                else if (dgJ == dgI)
                {
                    if (gfJ > gfI) intercambiar = true;
                    else if (gfJ == gfI)
                    {
                        // Sorteo final en caso de empate total.
                        if ((rand() % 2) == 1) intercambiar = true;
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
    return orden.getCantidad() >= 1 ? orden[0] : 0;
}

Equipo* Grupo::getSegundo() const
{
    Lista<Equipo*> orden = ordenarEquipos();
    return orden.getCantidad() >= 2 ? orden[1] : 0;
}

Equipo* Grupo::getTercero() const
{
    Lista<Equipo*> orden = ordenarEquipos();
    return orden.getCantidad() >= 3 ? orden[2] : 0;
}

void Grupo::imprimirTabla(ostream& os) const
{
    Lista<Equipo*> orden = ordenarEquipos();

    os << "\nTabla Grupo " << letra << "\n";
    os << "Pos | Equipo | Pts | GF | GC | DG | Confederacion\n";

    for (int i = 0; i < orden.getCantidad(); i++)
    {
        os << i + 1 << " | " << orden[i]->getPais()
           << " | " << getPuntosDeEquipo(orden[i])
           << " | " << getGolesFavorGrupo(orden[i])
           << " | " << getGolesContraGrupo(orden[i])
           << " | " << getDiferenciaGolGrupo(orden[i])
           << " | " << orden[i]->getConfederacion() << "\n";
    }
}

void Grupo::imprimirPartidos(ostream& os) const
{
    os << "\nPartidos Grupo " << letra << "\n";

    for (int i = 0; i < partidos.getCantidad(); i++)
    {
        os << *partidos[i] << "\n";
    }
}

ostream& operator<<(ostream& os, const Grupo& grupo)
{
    os << "Grupo " << grupo.letra << "\n";

    for (int i = 0; i < grupo.equipos.getCantidad(); i++)
    {
        os << "- " << grupo.equipos[i]->getPais()
           << " (" << grupo.equipos[i]->getConfederacion() << ")\n";
    }

    return os;
}

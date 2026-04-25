#include "grupo.h"
#include "partido.h"

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
    // Se aplica la regla del sorteo: máximo dos UEFA o una sola de cualquier otra confederación.
    if (equipo == nullptr)
    {
        return false;
    }

    int uefa = 0;

    for (int i = 0; i < equipos.getCantidad(); i++)
    {
        if (equipos[i]->getConfederacion() == equipo->getConfederacion())
        {
            if (equipo->getConfederacion() == "UEFA")
            {
                uefa++;
            }
            else
            {
                return false;
            }
        }
    }

    return equipo->getConfederacion() != "UEFA" || uefa < 2;
}

bool Grupo::agregarEquipo(Equipo* equipo)
{
    if (equipo == nullptr || equipos.getCantidad() >= 4)
    {
        return false;
    }

    if (!validarConfederacion(equipo))
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

    equipos.agregar(equipo);
    return true;
}

void Grupo::agregarPartido(Partido* partido)
{
    if (partido == nullptr)
    {
        return;
    }

    for (int i = 0; i < partidos.getCantidad(); i++)
    {
        if (partidos[i] == partido)
        {
            return;
        }
    }

    partidos.agregar(partido);
}

void Grupo::generarPartidos(const Fecha& fechaBase, const std::string& etapa)
{
    // Se usa un todos-contra-todos fijo de 6 partidos con 3 días de descanso entre jornadas.
    if (equipos.getCantidad() != 4)
    {
        return;
    }

    int cruces[6][2] = {{0, 1}, {2, 3}, {0, 2}, {1, 3}, {0, 3}, {1, 2}};
    int dias[6] = {0, 0, 3, 3, 6, 6};

    for (int i = 0; i < 6; i++)
    {
        Fecha fechaPartido = fechaBase;
        fechaPartido.avanzarDias(dias[i]);
        Partido* nuevo = new Partido(equipos[cruces[i][0]], equipos[cruces[i][1]], fechaPartido, etapa);
        nuevo->configurar("nombreSede", "00:00");
        nuevo->setArbitros("codArbitro1", "codArbitro2", "codArbitro3");
        partidos.agregar(nuevo);
    }
}

void Grupo::simularPartidos()
{
    for (int i = 0; i < partidos.getCantidad(); i++)
    {
        partidos[i]->simular();
    }
}

Lista<Equipo*> Grupo::ordenarEquipos() const
{
    // El desempate sigue el orden básico: puntos, diferencia de gol, goles a favor y país.
    Lista<Equipo*> orden = equipos;

    for (int i = 0; i < orden.getCantidad() - 1; i++)
    {
        for (int j = i + 1; j < orden.getCantidad(); j++)
        {
            bool intercambiar = false;

            if (orden[j]->getPuntosGrupo() > orden[i]->getPuntosGrupo())
            {
                intercambiar = true;
            }
            else if (orden[j]->getPuntosGrupo() == orden[i]->getPuntosGrupo())
            {
                if (orden[j]->getDiferenciaGol() > orden[i]->getDiferenciaGol())
                {
                    intercambiar = true;
                }
                else if (orden[j]->getDiferenciaGol() == orden[i]->getDiferenciaGol())
                {
                    if (orden[j]->getGolesFavor() > orden[i]->getGolesFavor())
                    {
                        intercambiar = true;
                    }
                    else if (orden[j]->getGolesFavor() == orden[i]->getGolesFavor() &&
                             orden[j]->getPais() < orden[i]->getPais())
                    {
                        intercambiar = true;
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

    if (orden.getCantidad() >= 1)
    {
        return orden[0];
    }

    return nullptr;
}

Equipo* Grupo::getSegundo() const
{
    Lista<Equipo*> orden = ordenarEquipos();

    if (orden.getCantidad() >= 2)
    {
        return orden[1];
    }

    return nullptr;
}

Equipo* Grupo::getTercero() const
{
    Lista<Equipo*> orden = ordenarEquipos();

    if (orden.getCantidad() >= 3)
    {
        return orden[2];
    }

    return nullptr;
}

void Grupo::imprimirTabla(std::ostream& os) const
{
    Lista<Equipo*> orden = ordenarEquipos();
    os << "Tabla del grupo " << letra << "\n";

    for (int i = 0; i < orden.getCantidad(); i++)
    {
        os << i + 1 << ". " << orden[i]->getPais()
           << " | Pts: " << orden[i]->getPuntosGrupo()
           << " | DG: " << orden[i]->getDiferenciaGol()
           << " | GF: " << orden[i]->getGolesFavor() << "\n";
    }
}

void Grupo::imprimirPartidos(std::ostream& os) const
{
    for (int i = 0; i < partidos.getCantidad(); i++)
    {
        os << *partidos[i] << "\n";
    }
}

std::ostream& operator<<(std::ostream& os, const Grupo& g)
{
    os << "Grupo " << g.letra << "\n";

    for (int i = 0; i < g.equipos.getCantidad(); i++)
    {
        os << "- " << g.equipos[i]->getPais()
           << " (" << g.equipos[i]->getConfederacion() << ")\n";
    }

    return os;
}

#include "torneo.h"

#include <cstdlib>
#include <fstream>
#include <sstream>

Torneo::Torneo()
{
    nombre = "UdeAWorldCup";
    campeon = nullptr;
    subcampeon = nullptr;
    tercerLugar = nullptr;
    cuartoLugar = nullptr;
}

Torneo::Torneo(const std::string& nombre)
{
    this->nombre = nombre;
    campeon = nullptr;
    subcampeon = nullptr;
    tercerLugar = nullptr;
    cuartoLugar = nullptr;
}

Torneo::~Torneo()
{
    for (int i = 0; i < partidos.getCantidad(); i++)
    {
        delete partidos[i];
    }

    for (int i = 0; i < grupos.getCantidad(); i++)
    {
        delete grupos[i];
    }

    for (int i = 0; i < equipos.getCantidad(); i++)
    {
        delete equipos[i];
    }
}

void Torneo::limpiarBombos()
{
    bombo1.limpiar();
    bombo2.limpiar();
    bombo3.limpiar();
    bombo4.limpiar();
}

void Torneo::limpiarClasificados()
{
    clasificadosR16.limpiar();
    clasificadosR8.limpiar();
    clasificadosR4.limpiar();
    finalistas.limpiar();
}

void Torneo::ordenarEquiposPorRanking(Lista<Equipo*>& lista) const
{
    for (int i = 0; i < lista.getCantidad() - 1; i++)
    {
        for (int j = i + 1; j < lista.getCantidad(); j++)
        {
            if (*lista[j] < *lista[i])
            {
                Equipo* aux = lista[i];
                lista[i] = lista[j];
                lista[j] = aux;
            }
        }
    }
}

Equipo* Torneo::extraerAleatorioDeLista(Lista<Equipo*>& lista)
{
    if (lista.estaVacia())
    {
        return nullptr;
    }

    int indice = std::rand() % lista.getCantidad();
    Equipo* equipo = lista[indice];
    lista.eliminar(indice);
    return equipo;
}

void Torneo::agregarEquipo(Equipo* equipo)
{
    if (equipo != nullptr)
    {
        equipos.agregar(equipo);
        recursos.contarBytes(sizeof(Equipo));
    }
}

void Torneo::cargarDatosEquipos(const std::string& archivo)
{
    // Se asume un CSV simple separado por comas, sin librerías externas.
    std::ifstream entrada(archivo.c_str());
    if (!entrada.is_open())
    {
        return;
    }

    std::string linea;
    std::getline(entrada, linea);

    while (std::getline(entrada, linea))
    {
        if (linea.empty())
        {
            continue;
        }

        std::stringstream ss(linea);
        std::string pais;
        std::string director;
        std::string federacion;
        std::string confederacion;
        std::string dato;

        std::getline(ss, pais, ',');
        std::getline(ss, director, ',');
        std::getline(ss, federacion, ',');
        std::getline(ss, confederacion, ',');

        int ranking = 0;
        int gf = 0;
        int gc = 0;
        int pg = 0;
        int pe = 0;
        int pp = 0;

        std::getline(ss, dato, ',');
        if (!dato.empty()) ranking = std::atoi(dato.c_str());
        std::getline(ss, dato, ',');
        if (!dato.empty()) gf = std::atoi(dato.c_str());
        std::getline(ss, dato, ',');
        if (!dato.empty()) gc = std::atoi(dato.c_str());
        std::getline(ss, dato, ',');
        if (!dato.empty()) pg = std::atoi(dato.c_str());
        std::getline(ss, dato, ',');
        if (!dato.empty()) pe = std::atoi(dato.c_str());
        std::getline(ss, dato, ',');
        if (!dato.empty()) pp = std::atoi(dato.c_str());

        agregarEquipo(new Equipo(pais, director, federacion, confederacion, ranking, gf, gc, pg, pe, pp));
        recursos.contarIteracion();
    }
}

void Torneo::crearJugadoresArtificiales()
{
    // Se fabrican los 26 jugadores por equipo y se reparten los goles históricos.
    for (int i = 0; i < equipos.getCantidad(); i++)
    {
        Equipo* equipo = equipos[i];

        if (equipo->getCantidadJugadores() > 0)
        {
            continue;
        }

        for (int j = 1; j <= 26; j++)
        {
            std::string numero = std::to_string(j);
            Jugador* jugador = new Jugador("nombre" + numero, "apellido" + numero, j);
            equipo->agregarJugador(jugador);
            recursos.contarBytes(sizeof(Jugador));
        }

        int golesPorRepartir = equipo->getGolesFavor();
        int indice = 0;

        while (golesPorRepartir > 0 && equipo->getCantidadJugadores() > 0)
        {
            equipo->getJugador(indice)->sumarGol();
            golesPorRepartir--;
            indice = (indice + 1) % equipo->getCantidadJugadores();
        }
    }
}

void Torneo::guardarDatosJugadores(const std::string& archivo)
{
    std::ofstream salida(archivo.c_str());
    if (!salida.is_open())
    {
        return;
    }

    salida << "pais,nombre,apellido,camiseta,partidos,goles,minutos,asistencias,amarillas,rojas,faltas\n";

    for (int i = 0; i < equipos.getCantidad(); i++)
    {
        for (int j = 0; j < equipos[i]->getCantidadJugadores(); j++)
        {
            Jugador* jugador = equipos[i]->getJugador(j);
            salida << equipos[i]->getPais() << ","
                   << jugador->getNombre() << ","
                   << jugador->getApellido() << ","
                   << jugador->getNumeroCamiseta() << ","
                   << jugador->getPartidosJugados() << ","
                   << jugador->getGoles() << ","
                   << jugador->getMinutosJugados() << ","
                   << jugador->getAsistencias() << ","
                   << jugador->getTarjetasAmarillas() << ","
                   << jugador->getTarjetasRojas() << ","
                   << jugador->getFaltas() << "\n";
        }
    }
}

void Torneo::crearBombos()
{
    // El anfitrión se fuerza al bombo 1 y el resto se reparte por ranking FIFA.
    limpiarBombos();

    Lista<Equipo*> ordenados = equipos;
    ordenarEquiposPorRanking(ordenados);

    for (int i = 0; i < ordenados.getCantidad(); i++)
    {
        if (ordenados[i]->getPais() == "Estados Unidos" || ordenados[i]->getPais() == "EE. UU." || ordenados[i]->getPais() == "USA")
        {
            bombo1.agregar(ordenados[i]);
            ordenados.eliminar(i);
            break;
        }
    }

    for (int i = 0; i < ordenados.getCantidad(); i++)
    {
        if (bombo1.getCantidad() < 12) bombo1.agregar(ordenados[i]);
        else if (bombo2.getCantidad() < 12) bombo2.agregar(ordenados[i]);
        else if (bombo3.getCantidad() < 12) bombo3.agregar(ordenados[i]);
        else bombo4.agregar(ordenados[i]);
    }
}

Equipo* Torneo::extraerEquipoDeBombo(int numeroBombo)
{
    if (numeroBombo == 1) return extraerAleatorioDeLista(bombo1);
    if (numeroBombo == 2) return extraerAleatorioDeLista(bombo2);
    if (numeroBombo == 3) return extraerAleatorioDeLista(bombo3);
    if (numeroBombo == 4) return extraerAleatorioDeLista(bombo4);
    return nullptr;
}

void Torneo::formarGrupos()
{
    // El sorteo intenta insertar equipos respetando la restricción por confederación.
    for (int i = 0; i < grupos.getCantidad(); i++)
    {
        delete grupos[i];
    }
    grupos.limpiar();

    for (int i = 0; i < 12; i++)
    {
        grupos.agregar(new Grupo(static_cast<char>('A' + i)));
    }

    Lista<Equipo*>* bombos[4] = {&bombo1, &bombo2, &bombo3, &bombo4};

    for (int b = 0; b < 4; b++)
    {
        for (int g = 0; g < 12; g++)
        {
            bool agregado = false;
            int intentos = 0;

            while (!agregado && !bombos[b]->estaVacia() && intentos < 50)
            {
                Equipo* candidato = extraerAleatorioDeLista(*bombos[b]);

                if (grupos[g]->agregarEquipo(candidato))
                {
                    agregado = true;
                }
                else
                {
                    bombos[b]->agregar(candidato);
                }

                intentos++;
            }
        }
    }
}

void Torneo::configurarPartidosGrupos()
{
    // Cada grupo se desfasa un día para no concentrar todas las jornadas a la vez.
    for (int i = 0; i < partidos.getCantidad(); i++)
    {
        delete partidos[i];
    }
    partidos.limpiar();

    Fecha inicio(20, 6, 2026);

    for (int i = 0; i < grupos.getCantidad(); i++)
    {
        Fecha base = inicio;
        base.avanzarDias(i);
        grupos[i]->generarPartidos(base, "GRUPOS");

        for (int j = 0; j < grupos[i]->getPartidos().getCantidad(); j++)
        {
            partidos.agregar(grupos[i]->getPartidos()[j]);
        }
    }
}

void Torneo::simularFaseGrupos()
{
    for (int i = 0; i < grupos.getCantidad(); i++)
    {
        grupos[i]->simularPartidos();
    }
}

void Torneo::clasificarADieciseisavos()
{
    // Se toman primeros, segundos y luego una selección simple de terceros.
    limpiarClasificados();
    Lista<Equipo*> terceros;

    for (int i = 0; i < grupos.getCantidad(); i++)
    {
        if (grupos[i]->getPrimero() != nullptr) clasificadosR16.agregar(grupos[i]->getPrimero());
        if (grupos[i]->getSegundo() != nullptr) clasificadosR16.agregar(grupos[i]->getSegundo());
        if (grupos[i]->getTercero() != nullptr) terceros.agregar(grupos[i]->getTercero());
    }

    ordenarEquiposPorRanking(terceros);

    for (int i = 0; i < terceros.getCantidad() && i < 8; i++)
    {
        clasificadosR16.agregar(terceros[i]);
    }
}

const Lista<Equipo*>& Torneo::getEquipos() const
{
    return equipos;
}

const Lista<Grupo*>& Torneo::getGrupos() const
{
    return grupos;
}

const Lista<Partido*>& Torneo::getPartidos() const
{
    return partidos;
}

const Lista<Equipo*>& Torneo::getClasificadosR16() const
{
    return clasificadosR16;
}

Recursos& Torneo::getRecursos()
{
    return recursos;
}

const Recursos& Torneo::getRecursos() const
{
    return recursos;
}

void Torneo::mostrarRecursos(std::ostream& os) const
{
    os << recursos;
}

#include "partido.h"

#include <cstdlib>

Partido::Partido()
{
    hora = "00:00";
    sede = "nombreSede";
    arbitro1 = "codArbitro1";
    arbitro2 = "codArbitro2";
    arbitro3 = "codArbitro3";
    equipo1 = nullptr;
    equipo2 = nullptr;
    golesEquipo1 = 0;
    golesEquipo2 = 0;
    posesionEquipo1 = 50.0f;
    posesionEquipo2 = 50.0f;
    prorroga = false;
    etapa = "";
}

Partido::Partido(Equipo* equipo1, Equipo* equipo2, const Fecha& fecha, const std::string& etapa)
{
    this->fecha = fecha;
    hora = "00:00";
    sede = "nombreSede";
    arbitro1 = "codArbitro1";
    arbitro2 = "codArbitro2";
    arbitro3 = "codArbitro3";
    this->equipo1 = equipo1;
    this->equipo2 = equipo2;
    golesEquipo1 = 0;
    golesEquipo2 = 0;
    posesionEquipo1 = 50.0f;
    posesionEquipo2 = 50.0f;
    prorroga = false;
    this->etapa = etapa;
}

Partido::~Partido()
{
    liberarConvocados();
}

void Partido::liberarConvocados()
{
    for (int i = 0; i < convocadosEquipo1.getCantidad(); i++)
    {
        delete convocadosEquipo1[i];
    }

    for (int i = 0; i < convocadosEquipo2.getCantidad(); i++)
    {
        delete convocadosEquipo2[i];
    }

    convocadosEquipo1.limpiar();
    convocadosEquipo2.limpiar();
}

void Partido::configurar(const std::string& sede, const std::string& hora)
{
    this->sede = sede;
    this->hora = hora;
}

void Partido::setArbitros(const std::string& arbitro1, const std::string& arbitro2, const std::string& arbitro3)
{
    this->arbitro1 = arbitro1;
    this->arbitro2 = arbitro2;
    this->arbitro3 = arbitro3;
}

int Partido::calcularGolesEsperados(Equipo* atacante, Equipo* defensor) const
{
    if (atacante == nullptr || defensor == nullptr)
    {
        return 0;
    }

    int partidosAtacante = atacante->getPartidosTotales();
    int partidosDefensor = defensor->getPartidosTotales();
    float promedioGF = partidosAtacante > 0 ? static_cast<float>(atacante->getGolesFavor()) / partidosAtacante : 1.0f;
    float promedioGC = partidosDefensor > 0 ? static_cast<float>(defensor->getGolesContra()) / partidosDefensor : 1.0f;
    float lambda = (0.6f * promedioGF + 0.4f * promedioGC) * 1.35f;
    int base = static_cast<int>(lambda);
    int decimal = static_cast<int>((lambda - base) * 100.0f);

    if ((std::rand() % 100) < decimal)
    {
        base++;
    }

    return base < 0 ? 0 : base;
}

void Partido::seleccionarConvocados()
{
    // En esta versión simple se eligen 11 jugadores al azar sin cambios durante el partido.
    liberarConvocados();

    if (equipo1 == nullptr || equipo2 == nullptr)
    {
        return;
    }

    Equipo* equipos[2] = {equipo1, equipo2};
    Lista<RegistroJugadorPartido*>* listas[2] = {&convocadosEquipo1, &convocadosEquipo2};

    for (int e = 0; e < 2; e++)
    {
        int cantidad = equipos[e]->getCantidadJugadores();
        int convocados = cantidad < 11 ? cantidad : 11;
        int* indices = new int[cantidad];

        for (int i = 0; i < cantidad; i++)
        {
            indices[i] = i;
        }

        for (int i = 0; i < convocados; i++)
        {
            int posAleatoria = i + (std::rand() % (cantidad - i));
            int aux = indices[i];
            indices[i] = indices[posAleatoria];
            indices[posAleatoria] = aux;
            listas[e]->agregar(new RegistroJugadorPartido(equipos[e]->getJugador(indices[i])));
        }

        delete[] indices;
    }
}

void Partido::calcularPosesion()
{
    // La posesión se estima con un modelo proporcional al ranking FIFA de ambos equipos.
    if (equipo1 == nullptr || equipo2 == nullptr)
    {
        posesionEquipo1 = 50.0f;
        posesionEquipo2 = 50.0f;
        return;
    }

    float fuerza1 = 200.0f - equipo1->getRankingFIFA();
    float fuerza2 = 200.0f - equipo2->getRankingFIFA();
    float total = fuerza1 + fuerza2;

    if (total <= 0.0f)
    {
        posesionEquipo1 = 50.0f;
        posesionEquipo2 = 50.0f;
        return;
    }

    posesionEquipo1 = (fuerza1 * 100.0f) / total;
    posesionEquipo2 = 100.0f - posesionEquipo1;
}

void Partido::asignarEventosJugadores(Lista<RegistroJugadorPartido*>& convocados, int golesDelEquipo, int minutosBase)
{
    // Aquí se simulan eventos individuales con probabilidades fijas del enunciado.
    for (int i = 0; i < convocados.getCantidad(); i++)
    {
        convocados[i]->setMinutos(minutosBase);

        if ((std::rand() % 10000) < 600)
        {
            convocados[i]->registrarAmarilla();

            if ((std::rand() % 10000) < 115)
            {
                convocados[i]->registrarAmarilla();
                convocados[i]->registrarRoja();
            }
        }

        if ((std::rand() % 10000) < 1300)
        {
            convocados[i]->registrarFalta();
            if ((std::rand() % 10000) < 275)
            {
                convocados[i]->registrarFalta();
                if ((std::rand() % 10000) < 70)
                {
                    convocados[i]->registrarFalta();
                }
            }
        }
    }

    for (int g = 0; g < golesDelEquipo && convocados.getCantidad() > 0; g++)
    {
        int intentos = 0;
        bool asignado = false;

        while (!asignado && intentos < 40)
        {
            int indice = std::rand() % convocados.getCantidad();
            if ((std::rand() % 10000) < 400)
            {
                convocados[indice]->incrementarGol();
                asignado = true;
            }
            intentos++;
        }

        if (!asignado)
        {
            convocados[g % convocados.getCantidad()]->incrementarGol();
        }
    }
}

void Partido::simularGoles()
{
    golesEquipo1 = calcularGolesEsperados(equipo1, equipo2);
    golesEquipo2 = calcularGolesEsperados(equipo2, equipo1);
}

void Partido::simularTarjetasYFaltas()
{
    int minutosBase = prorroga ? 120 : 90;
    asignarEventosJugadores(convocadosEquipo1, golesEquipo1, minutosBase);
    asignarEventosJugadores(convocadosEquipo2, golesEquipo2, minutosBase);
}

void Partido::resolverEmpate()
{
    // En eliminación directa se rompe el empate sesgando el azar con el ranking FIFA.
    if (etapa == "GRUPOS" || golesEquipo1 != golesEquipo2)
    {
        return;
    }

    prorroga = true;
    int sesgo = 50 + (equipo2->getRankingFIFA() - equipo1->getRankingFIFA());
    if (sesgo < 15) sesgo = 15;
    if (sesgo > 85) sesgo = 85;

    if ((std::rand() % 100) < sesgo)
    {
        golesEquipo1++;
    }
    else
    {
        golesEquipo2++;
    }
}

int Partido::sumarTarjetas(const Lista<RegistroJugadorPartido*>& convocados) const
{
    int total = 0;
    for (int i = 0; i < convocados.getCantidad(); i++)
    {
        total += convocados[i]->getTarjetasAmarillas();
    }
    return total;
}

int Partido::sumarRojas(const Lista<RegistroJugadorPartido*>& convocados) const
{
    int total = 0;
    for (int i = 0; i < convocados.getCantidad(); i++)
    {
        total += convocados[i]->getTarjetasRojas();
    }
    return total;
}

int Partido::sumarFaltas(const Lista<RegistroJugadorPartido*>& convocados) const
{
    int total = 0;
    for (int i = 0; i < convocados.getCantidad(); i++)
    {
        total += convocados[i]->getFaltas();
    }
    return total;
}

void Partido::actualizarHistoricos()
{
    // Primero se actualizan los jugadores y luego el acumulado del equipo.
    if (equipo1 == nullptr || equipo2 == nullptr)
    {
        return;
    }

    for (int i = 0; i < convocadosEquipo1.getCantidad(); i++)
    {
        convocadosEquipo1[i]->actualizarHistorico();
    }

    for (int i = 0; i < convocadosEquipo2.getCantidad(); i++)
    {
        convocadosEquipo2[i]->actualizarHistorico();
    }

    equipo1->actualizarEstadisticas(golesEquipo1, golesEquipo2, sumarTarjetas(convocadosEquipo1), sumarRojas(convocadosEquipo1), sumarFaltas(convocadosEquipo1));
    equipo2->actualizarEstadisticas(golesEquipo2, golesEquipo1, sumarTarjetas(convocadosEquipo2), sumarRojas(convocadosEquipo2), sumarFaltas(convocadosEquipo2));

    if (etapa == "GRUPOS")
    {
        if (golesEquipo1 > golesEquipo2)
        {
            equipo1->sumarPuntos(3);
        }
        else if (golesEquipo2 > golesEquipo1)
        {
            equipo2->sumarPuntos(3);
        }
        else
        {
            equipo1->sumarPuntos(1);
            equipo2->sumarPuntos(1);
        }
    }
}

void Partido::simular()
{
    seleccionarConvocados();
    calcularPosesion();
    simularGoles();
    resolverEmpate();
    simularTarjetasYFaltas();
    actualizarHistoricos();
}

Equipo* Partido::getEquipo1() const
{
    return equipo1;
}

Equipo* Partido::getEquipo2() const
{
    return equipo2;
}

int Partido::getGolesEquipo1() const
{
    return golesEquipo1;
}

int Partido::getGolesEquipo2() const
{
    return golesEquipo2;
}

Equipo* Partido::getGanador() const
{
    if (golesEquipo1 > golesEquipo2) return equipo1;
    if (golesEquipo2 > golesEquipo1) return equipo2;
    return nullptr;
}

bool Partido::huboProrroga() const
{
    return prorroga;
}

Fecha Partido::getFecha() const
{
    return fecha;
}

std::string Partido::getEtapa() const
{
    return etapa;
}

const Lista<RegistroJugadorPartido*>& Partido::getConvocadosEquipo1() const
{
    return convocadosEquipo1;
}

const Lista<RegistroJugadorPartido*>& Partido::getConvocadosEquipo2() const
{
    return convocadosEquipo2;
}

std::ostream& operator<<(std::ostream& os, const Partido& partido)
{
    os << partido.fecha << " " << partido.hora
       << " | " << partido.sede
       << " | " << (partido.equipo1 != nullptr ? partido.equipo1->getPais() : "TBD")
       << " " << partido.golesEquipo1
       << " - " << partido.golesEquipo2 << " "
       << (partido.equipo2 != nullptr ? partido.equipo2->getPais() : "TBD")
       << " | Posesion: " << partido.posesionEquipo1 << "% - " << partido.posesionEquipo2 << "%";

    if (partido.prorroga)
    {
        os << " | Resuelto en prorroga";
    }

    return os;
}

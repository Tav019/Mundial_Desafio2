#include "partido.h"

using namespace std;

#include <cstdlib>

Partido::Partido()
{
    hora = "00:00";
    sede = "nombreSede";
    arbitro1 = "codArbitro1";
    arbitro2 = "codArbitro2";
    arbitro3 = "codArbitro3";
    equipo1 = 0;
    equipo2 = 0;
    golesEquipo1 = 0;
    golesEquipo2 = 0;
    posesionEquipo1 = 50.0f;
    posesionEquipo2 = 50.0f;
    prorroga = false;
    etapa = "";
    simulado = false;
}

Partido::Partido(Equipo* equipo1, Equipo* equipo2, const Fecha& fecha, const string& etapa)
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
    simulado = false;
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

void Partido::configurar(const string& sede, const string& hora)
{
    this->sede = sede;
    this->hora = hora;
}

void Partido::setArbitros(const string& arbitro1, const string& arbitro2, const string& arbitro3)
{
    this->arbitro1 = arbitro1;
    this->arbitro2 = arbitro2;
    this->arbitro3 = arbitro3;
}

int Partido::calcularGolesEsperados(Equipo* atacante, Equipo* defensor) const
{
    if (atacante == 0 || defensor == 0)
    {
        return 0;
    }

    int partidosAtacante = atacante->getPartidosTotales();
    int partidosDefensor = defensor->getPartidosTotales();

    float promedioGF = partidosAtacante > 0 ? static_cast<float>(atacante->getGolesFavor()) / partidosAtacante : 1.0f;
    float promedioGC = partidosDefensor > 0 ? static_cast<float>(defensor->getGolesContra()) / partidosDefensor : 1.0f;

    // Modelo simple basado en la ecuación pedida: mezcla ofensiva del atacante y defensiva del rival.
    float lambda = (0.60f * promedioGF + 0.40f * promedioGC) * 1.15f;

    if (lambda < 0.20f) lambda = 0.20f;
    if (lambda > 5.00f) lambda = 5.00f;

    int goles = static_cast<int>(lambda);
    int probabilidadDecimal = static_cast<int>((lambda - goles) * 100.0f);

    if ((rand() % 100) < probabilidadDecimal)
    {
        goles++;
    }

    // Pequeña variación aleatoria para que no todos los partidos sean demasiado repetitivos.
    if ((rand() % 100) < 18 && goles > 0) goles--;
    if ((rand() % 100) < 22) goles++;

    return goles;
}

void Partido::seleccionarConvocados()
{
    liberarConvocados();

    if (equipo1 == 0 || equipo2 == 0)
    {
        return;
    }

    Equipo* equipos[2] = {equipo1, equipo2};
    Lista<RegistroJugadorPartido*>* listas[2] = {&convocadosEquipo1, &convocadosEquipo2};

    for (int e = 0; e < 2; e++)
    {
        int cantidad = equipos[e]->getCantidadJugadores();
        int cantidadConvocados = cantidad < 11 ? cantidad : 11;

        if (cantidad <= 0)
        {
            continue;
        }

        int* indices = new int[cantidad];

        for (int i = 0; i < cantidad; i++)
        {
            indices[i] = i;
        }

        for (int i = 0; i < cantidadConvocados; i++)
        {
            int posicionAleatoria = i + (rand() % (cantidad - i));
            int auxiliar = indices[i];
            indices[i] = indices[posicionAleatoria];
            indices[posicionAleatoria] = auxiliar;
            listas[e]->agregar(new RegistroJugadorPartido(equipos[e]->getJugador(indices[i])));
        }

        delete[] indices;
    }
}

void Partido::calcularPosesion()
{
    if (equipo1 == 0 || equipo2 == 0)
    {
        posesionEquipo1 = 50.0f;
        posesionEquipo2 = 50.0f;
        return;
    }

    float fuerza1 = 220.0f - equipo1->getRankingFIFA();
    float fuerza2 = 220.0f - equipo2->getRankingFIFA();

    if (fuerza1 < 10.0f) fuerza1 = 10.0f;
    if (fuerza2 < 10.0f) fuerza2 = 10.0f;

    float total = fuerza1 + fuerza2;
    posesionEquipo1 = (fuerza1 * 100.0f) / total;
    posesionEquipo2 = 100.0f - posesionEquipo1;
}

void Partido::asignarEventosJugadores(Lista<RegistroJugadorPartido*>& convocados, int golesDelEquipo, int minutosBase)
{
    for (int i = 0; i < convocados.getCantidad(); i++)
    {
        convocados[i]->setMinutos(minutosBase);

        if ((rand() % 10000) < 600)
        {
            convocados[i]->registrarAmarilla();

            if ((rand() % 10000) < 115)
            {
                convocados[i]->registrarAmarilla();
                convocados[i]->registrarRoja();
            }
        }

        if ((rand() % 10000) < 1300)
        {
            convocados[i]->registrarFalta();

            if ((rand() % 10000) < 275)
            {
                convocados[i]->registrarFalta();

                if ((rand() % 10000) < 70)
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
            int indice = rand() % convocados.getCantidad();

            if ((rand() % 10000) < 400)
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
    if (etapa == "GRUPOS" || equipo1 == 0 || equipo2 == 0 || golesEquipo1 != golesEquipo2)
    {
        return;
    }

    prorroga = true;
    int sesgoEquipo1 = 50 + (equipo2->getRankingFIFA() - equipo1->getRankingFIFA());

    if (sesgoEquipo1 < 15) sesgoEquipo1 = 15;
    if (sesgoEquipo1 > 85) sesgoEquipo1 = 85;

    if ((rand() % 100) < sesgoEquipo1)
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
    for (int i = 0; i < convocados.getCantidad(); i++) total += convocados[i]->getTarjetasAmarillas();
    return total;
}

int Partido::sumarRojas(const Lista<RegistroJugadorPartido*>& convocados) const
{
    int total = 0;
    for (int i = 0; i < convocados.getCantidad(); i++) total += convocados[i]->getTarjetasRojas();
    return total;
}

int Partido::sumarFaltas(const Lista<RegistroJugadorPartido*>& convocados) const
{
    int total = 0;
    for (int i = 0; i < convocados.getCantidad(); i++) total += convocados[i]->getFaltas();
    return total;
}

void Partido::actualizarHistoricos()
{
    if (simulado || equipo1 == 0 || equipo2 == 0)
    {
        return;
    }

    for (int i = 0; i < convocadosEquipo1.getCantidad(); i++) convocadosEquipo1[i]->actualizarHistorico();
    for (int i = 0; i < convocadosEquipo2.getCantidad(); i++) convocadosEquipo2[i]->actualizarHistorico();

    equipo1->actualizarEstadisticas(golesEquipo1, golesEquipo2, sumarTarjetas(convocadosEquipo1), sumarRojas(convocadosEquipo1), sumarFaltas(convocadosEquipo1));
    equipo2->actualizarEstadisticas(golesEquipo2, golesEquipo1, sumarTarjetas(convocadosEquipo2), sumarRojas(convocadosEquipo2), sumarFaltas(convocadosEquipo2));

    if (etapa == "GRUPOS")
    {
        if (golesEquipo1 > golesEquipo2) equipo1->sumarPuntos(3);
        else if (golesEquipo2 > golesEquipo1) equipo2->sumarPuntos(3);
        else
        {
            equipo1->sumarPuntos(1);
            equipo2->sumarPuntos(1);
        }
    }

    simulado = true;
}

void Partido::simular()
{
    if (simulado) return;

    seleccionarConvocados();
    calcularPosesion();
    simularGoles();
    resolverEmpate();
    simularTarjetasYFaltas();
    actualizarHistoricos();
}

Equipo* Partido::getEquipo1() const { return equipo1; }
Equipo* Partido::getEquipo2() const { return equipo2; }
int Partido::getGolesEquipo1() const { return golesEquipo1; }
int Partido::getGolesEquipo2() const { return golesEquipo2; }
float Partido::getPosesionEquipo1() const { return posesionEquipo1; }
float Partido::getPosesionEquipo2() const { return posesionEquipo2; }

Equipo* Partido::getGanador() const
{
    if (golesEquipo1 > golesEquipo2) return equipo1;
    if (golesEquipo2 > golesEquipo1) return equipo2;
    return 0;
}

Equipo* Partido::getPerdedor() const
{
    if (golesEquipo1 > golesEquipo2) return equipo2;
    if (golesEquipo2 > golesEquipo1) return equipo1;
    return 0;
}

bool Partido::huboProrroga() const { return prorroga; }
bool Partido::fueSimulado() const { return simulado; }
Fecha Partido::getFecha() const { return fecha; }
string Partido::getEtapa() const { return etapa; }
const Lista<RegistroJugadorPartido*>& Partido::getConvocadosEquipo1() const { return convocadosEquipo1; }
const Lista<RegistroJugadorPartido*>& Partido::getConvocadosEquipo2() const { return convocadosEquipo2; }

ostream& operator<<(ostream& os, const Partido& partido)
{
    os << "[" << partido.etapa << "] " << partido.fecha << " " << partido.hora
       << " | " << partido.sede << " | ";

    if (partido.equipo1 != 0) os << partido.equipo1->getPais();
    else os << "Equipo 1";

    os << " " << partido.golesEquipo1 << " - " << partido.golesEquipo2 << " ";

    if (partido.equipo2 != 0) os << partido.equipo2->getPais();
    else os << "Equipo 2";

    os << " | Posesion: " << partido.posesionEquipo1 << "% - " << partido.posesionEquipo2 << "%";

    if (partido.prorroga)
    {
        os << " | Resuelto en prorroga";
    }

    os << " | Arbitros: " << partido.arbitro1 << ", " << partido.arbitro2 << ", " << partido.arbitro3;

    os << "\nGoleadores " << (partido.equipo1 != 0 ? partido.equipo1->getPais() : "Equipo 1") << ": ";
    bool hayGoles = false;
    for (int i = 0; i < partido.convocadosEquipo1.getCantidad(); i++)
    {
        for (int g = 0; g < partido.convocadosEquipo1[i]->getGoles(); g++)
        {
            os << "#" << partido.convocadosEquipo1[i]->getJugador()->getNumeroCamiseta() << " ";
            hayGoles = true;
        }
    }
    if (!hayGoles) os << "Sin goles";

    os << "\nGoleadores " << (partido.equipo2 != 0 ? partido.equipo2->getPais() : "Equipo 2") << ": ";
    hayGoles = false;
    for (int i = 0; i < partido.convocadosEquipo2.getCantidad(); i++)
    {
        for (int g = 0; g < partido.convocadosEquipo2[i]->getGoles(); g++)
        {
            os << "#" << partido.convocadosEquipo2[i]->getJugador()->getNumeroCamiseta() << " ";
            hayGoles = true;
        }
    }
    if (!hayGoles) os << "Sin goles";

    return os;
}

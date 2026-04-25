#include "equipo.h"

Equipo::Equipo()
{
    pais = "";
    directorTecnico = "";
    federacion = "";
    confederacion = "";
    rankingFIFA = 0;
    golesFavor = 0;
    golesContra = 0;
    partidosGanados = 0;
    partidosEmpatados = 0;
    partidosPerdidos = 0;
    tarjetasAmarillas = 0;
    tarjetasRojas = 0;
    faltas = 0;
    puntosGrupo = 0;
}

Equipo::Equipo(const std::string& pais, int ranking, const std::string& confederacion)
{
    this->pais = pais;
    directorTecnico = "";
    federacion = "";
    this->confederacion = confederacion;
    rankingFIFA = ranking;
    golesFavor = 0;
    golesContra = 0;
    partidosGanados = 0;
    partidosEmpatados = 0;
    partidosPerdidos = 0;
    tarjetasAmarillas = 0;
    tarjetasRojas = 0;
    faltas = 0;
    puntosGrupo = 0;
}

Equipo::Equipo(const std::string& pais,
               const std::string& directorTecnico,
               const std::string& federacion,
               const std::string& confederacion,
               int ranking,
               int golesFavor,
               int golesContra,
               int ganados,
               int empatados,
               int perdidos)
{
    this->pais = pais;
    this->directorTecnico = directorTecnico;
    this->federacion = federacion;
    this->confederacion = confederacion;
    rankingFIFA = ranking;
    this->golesFavor = golesFavor;
    this->golesContra = golesContra;
    partidosGanados = ganados;
    partidosEmpatados = empatados;
    partidosPerdidos = perdidos;
    tarjetasAmarillas = 0;
    tarjetasRojas = 0;
    faltas = 0;
    puntosGrupo = 0;
}

Equipo::Equipo(const Equipo& otro)
{
    pais = otro.pais;
    directorTecnico = otro.directorTecnico;
    federacion = otro.federacion;
    confederacion = otro.confederacion;
    rankingFIFA = otro.rankingFIFA;
    golesFavor = otro.golesFavor;
    golesContra = otro.golesContra;
    partidosGanados = otro.partidosGanados;
    partidosEmpatados = otro.partidosEmpatados;
    partidosPerdidos = otro.partidosPerdidos;
    tarjetasAmarillas = otro.tarjetasAmarillas;
    tarjetasRojas = otro.tarjetasRojas;
    faltas = otro.faltas;
    puntosGrupo = otro.puntosGrupo;

    // Se hace copia profunda de la plantilla para que cada equipo dueño controle su memoria.
    for (int i = 0; i < otro.jugadores.getCantidad(); i++)
    {
        if (otro.jugadores[i] != nullptr)
        {
            jugadores.agregar(new Jugador(*otro.jugadores[i]));
        }
    }
}

Equipo::~Equipo()
{
    for (int i = 0; i < jugadores.getCantidad(); i++)
    {
        delete jugadores[i];
    }
}

std::string Equipo::getPais() const
{
    return pais;
}

std::string Equipo::getDirectorTecnico() const
{
    return directorTecnico;
}

std::string Equipo::getFederacion() const
{
    return federacion;
}

std::string Equipo::getConfederacion() const
{
    return confederacion;
}

int Equipo::getRankingFIFA() const
{
    return rankingFIFA;
}

int Equipo::getPuntosGrupo() const
{
    return puntosGrupo;
}

int Equipo::getGolesFavor() const
{
    return golesFavor;
}

int Equipo::getGolesContra() const
{
    return golesContra;
}

int Equipo::getDiferenciaGol() const
{
    return golesFavor - golesContra;
}

int Equipo::getPartidosTotales() const
{
    return partidosGanados + partidosEmpatados + partidosPerdidos;
}

int Equipo::getTarjetasAmarillas() const
{
    return tarjetasAmarillas;
}

int Equipo::getTarjetasRojas() const
{
    return tarjetasRojas;
}

int Equipo::getFaltas() const
{
    return faltas;
}

void Equipo::setDirectorTecnico(const std::string& directorTecnico)
{
    this->directorTecnico = directorTecnico;
}

void Equipo::setFederacion(const std::string& federacion)
{
    this->federacion = federacion;
}

void Equipo::setRankingFIFA(int rankingFIFA)
{
    this->rankingFIFA = rankingFIFA;
}

void Equipo::agregarJugador(Jugador* jugador)
{
    if (jugador != nullptr)
    {
        jugadores.agregar(jugador);
    }
}

Jugador* Equipo::getJugador(int pos) const
{
    if (pos < 0 || pos >= jugadores.getCantidad())
    {
        return nullptr;
    }

    return jugadores[pos];
}

int Equipo::getCantidadJugadores() const
{
    return jugadores.getCantidad();
}

Lista<Jugador*>& Equipo::getJugadores()
{
    return jugadores;
}

const Lista<Jugador*>& Equipo::getJugadores() const
{
    return jugadores;
}

void Equipo::actualizarEstadisticas(int gf, int gc, int amarillas, int rojas, int faltas)
{
    // Cada partido impacta directamente el histórico general del equipo.
    golesFavor += gf;
    golesContra += gc;
    tarjetasAmarillas += amarillas;
    tarjetasRojas += rojas;
    this->faltas += faltas;

    if (gf > gc)
    {
        partidosGanados++;
    }
    else if (gf == gc)
    {
        partidosEmpatados++;
    }
    else
    {
        partidosPerdidos++;
    }
}

void Equipo::sumarPuntos(int puntos)
{
    if (puntos > 0)
    {
        puntosGrupo += puntos;
    }
}

void Equipo::reiniciarPuntosGrupo()
{
    puntosGrupo = 0;
}

bool Equipo::operator<(const Equipo& otro) const
{
    if (rankingFIFA != otro.rankingFIFA)
    {
        return rankingFIFA < otro.rankingFIFA;
    }

    return pais < otro.pais;
}

bool Equipo::operator==(const Equipo& otro) const
{
    return pais == otro.pais;
}

std::ostream& operator<<(std::ostream& os, const Equipo& equipo)
{
    os << equipo.pais
       << " | Ranking FIFA: " << equipo.rankingFIFA
       << " | Confederacion: " << equipo.confederacion
       << " | GF: " << equipo.golesFavor
       << " | GC: " << equipo.golesContra
       << " | Pts grupo: " << equipo.puntosGrupo;

    return os;
}

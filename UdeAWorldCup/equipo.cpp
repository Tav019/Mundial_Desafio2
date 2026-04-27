#include "equipo.h"

using namespace std;

Equipo::Equipo()
{
    pais = "";
    directorTecnico = "";
    federacion = "";
    confederacion = "";
    rankingFIFA = 0;
    golesFavorBase = 0;
    golesContraBase = 0;
    partidosGanadosBase = 0;
    partidosEmpatadosBase = 0;
    partidosPerdidosBase = 0;
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

Equipo::Equipo(const string& _pais, int _rankingFIFA, const string& _confederacion)
{
    pais = _pais;
    directorTecnico = "DT_" + pais;
    federacion = "Federacion_" + pais;
    confederacion = _confederacion;
    rankingFIFA = _rankingFIFA;
    golesFavorBase = 0;
    golesContraBase = 0;
    partidosGanadosBase = 0;
    partidosEmpatadosBase = 0;
    partidosPerdidosBase = 0;
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

Equipo::Equipo(const string& _pais,const string& _directorTecnico, const string& _federacion,const string& _confederacion,
               int _rankingFIFA,int _golesFavor,int _golesContra,int _partidosGanados,int _partidosEmpatados,
               int _partidosPerdidos)
{
    pais = _pais;
    directorTecnico = _directorTecnico;
    federacion = _federacion;
    confederacion = _confederacion;
    rankingFIFA = _rankingFIFA;
    golesFavorBase = _golesFavor;
    golesContraBase = _golesContra;
    partidosGanadosBase = _partidosGanados;
    partidosEmpatadosBase = _partidosEmpatados;
    partidosPerdidosBase = _partidosPerdidos;
    golesFavor = _golesFavor;
    golesContra = _golesContra;
    partidosGanados = _partidosGanados;
    partidosEmpatados = _partidosEmpatados;
    partidosPerdidos = _partidosPerdidos;
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
    golesFavorBase = otro.golesFavorBase;
    golesContraBase = otro.golesContraBase;
    partidosGanadosBase = otro.partidosGanadosBase;
    partidosEmpatadosBase = otro.partidosEmpatadosBase;
    partidosPerdidosBase = otro.partidosPerdidosBase;
    golesFavor = otro.golesFavor;
    golesContra = otro.golesContra;
    partidosGanados = otro.partidosGanados;
    partidosEmpatados = otro.partidosEmpatados;
    partidosPerdidos = otro.partidosPerdidos;
    tarjetasAmarillas = otro.tarjetasAmarillas;
    tarjetasRojas = otro.tarjetasRojas;
    faltas = otro.faltas;
    puntosGrupo = otro.puntosGrupo;

    for (int i = 0; i < otro.jugadores.getCantidad(); i++)
    {
        jugadores.agregar(new Jugador(*otro.jugadores[i]));
    }
}

Equipo::~Equipo()
{
    for (int i = 0; i < jugadores.getCantidad(); i++)
    {
        delete jugadores[i];
    }
}

string Equipo::getPais() const { return pais; }
string Equipo::getDirectorTecnico() const { return directorTecnico; }
string Equipo::getFederacion() const { return federacion; }
string Equipo::getConfederacion() const { return confederacion; }
int Equipo::getRankingFIFA() const { return rankingFIFA; }
int Equipo::getGolesFavorBase() const { return golesFavorBase; }
int Equipo::getGolesContraBase() const { return golesContraBase; }
int Equipo::getPartidosGanadosBase() const { return partidosGanadosBase; }
int Equipo::getPartidosEmpatadosBase() const { return partidosEmpatadosBase; }
int Equipo::getPartidosPerdidosBase() const { return partidosPerdidosBase; }
int Equipo::getPartidosTotalesBase() const { return partidosGanadosBase + partidosEmpatadosBase + partidosPerdidosBase; }
int Equipo::getGolesFavor() const { return golesFavor; }
int Equipo::getGolesContra() const { return golesContra; }
int Equipo::getDiferenciaGol() const { return golesFavor - golesContra; }
int Equipo::getPartidosGanados() const { return partidosGanados; }
int Equipo::getPartidosEmpatados() const { return partidosEmpatados; }
int Equipo::getPartidosPerdidos() const { return partidosPerdidos; }
int Equipo::getPartidosTotales() const { return partidosGanados + partidosEmpatados + partidosPerdidos; }
int Equipo::getTarjetasAmarillas() const { return tarjetasAmarillas; }
int Equipo::getTarjetasRojas() const { return tarjetasRojas; }
int Equipo::getFaltas() const { return faltas; }
int Equipo::getPuntosGrupo() const { return puntosGrupo; }

void Equipo::setDirectorTecnico(const string& _directorTecnico) { directorTecnico = _directorTecnico; }
void Equipo::setFederacion(const string& _federacion) { federacion = _federacion; }
void Equipo::setConfederacion(const string& _confederacion) { confederacion = _confederacion; }
void Equipo::setRankingFIFA(int _rankingFIFA) { rankingFIFA = _rankingFIFA; }

void Equipo::agregarJugador(Jugador* jugador)
{
    if (jugador != 0)
    {
        jugadores.agregar(jugador);
    }
}

Jugador* Equipo::getJugador(int posicion) const
{
    if (posicion < 0 || posicion >= jugadores.getCantidad())
    {
        return 0;
    }

    return jugadores[posicion];
}

int Equipo::getCantidadJugadores() const { return jugadores.getCantidad(); }
Lista<Jugador*>& Equipo::getJugadores() { return jugadores; }
const Lista<Jugador*>& Equipo::getJugadores() const { return jugadores; }

void Equipo::actualizarEstadisticas(int gf, int gc, int amarillas, int rojas, int _faltas)
{
    golesFavor += gf;
    golesContra += gc;
    tarjetasAmarillas += amarillas;
    tarjetasRojas += rojas;
    faltas += _faltas;

    if (gf > gc) partidosGanados++;
    else if (gf < gc) partidosPerdidos++;
    else partidosEmpatados++;
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
    return rankingFIFA < otro.rankingFIFA;
}

bool Equipo::operator==(const Equipo& otro) const
{
    return pais == otro.pais;
}

ostream& operator<<(ostream& os, const Equipo& equipo)
{
    os << equipo.pais
       << " | Confederacion: " << equipo.confederacion
       << " | Ranking FIFA: " << equipo.rankingFIFA
       << " | GF: " << equipo.golesFavor
       << " | GC: " << equipo.golesContra
       << " | PG: " << equipo.partidosGanados
       << " | PE: " << equipo.partidosEmpatados
       << " | PP: " << equipo.partidosPerdidos
       << " | TA: " << equipo.tarjetasAmarillas
       << " | TR: " << equipo.tarjetasRojas
       << " | Faltas: " << equipo.faltas;
    return os;
}

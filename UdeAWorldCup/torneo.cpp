#include "torneo.h"

using namespace std;

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>

Torneo::Torneo()
{
    nombre = "UdeAWorldCup";
    campeon = 0;
    subcampeon = 0;
    tercerLugar = 0;
    cuartoLugar = 0;
    datosCargados = false;
    jugadoresCreados = false;
    bombosCreados = false;
    gruposFormados = false;
    partidosGruposConfigurados = false;
    faseGruposSimulada = false;
    dieciseisavosConfigurados = false;
    eliminatoriasSimuladas = false;
    srand(static_cast<unsigned int>(time(0)));
}

Torneo::Torneo(const string& nombre)
{
    this->nombre = nombre;
    campeon = 0;
    subcampeon = 0;
    tercerLugar = 0;
    cuartoLugar = 0;
    datosCargados = false;
    jugadoresCreados = false;
    bombosCreados = false;
    gruposFormados = false;
    partidosGruposConfigurados = false;
    faseGruposSimulada = false;
    dieciseisavosConfigurados = false;
    eliminatoriasSimuladas = false;
    srand(static_cast<unsigned int>(time(0)));
}

Torneo::~Torneo()
{
    liberarTodo();
}

void Torneo::liberarTodo()
{
    for (int i = 0; i < partidos.getCantidad(); i++) delete partidos[i];
    for (int i = 0; i < grupos.getCantidad(); i++) delete grupos[i];
    for (int i = 0; i < equipos.getCantidad(); i++) delete equipos[i];

    partidos.limpiar();
    grupos.limpiar();
    equipos.limpiar();
    limpiarBombos();
    limpiarClasificados();

    datosCargados = false;
    jugadoresCreados = false;
    bombosCreados = false;
    gruposFormados = false;
    partidosGruposConfigurados = false;
    faseGruposSimulada = false;
    dieciseisavosConfigurados = false;
    eliminatoriasSimuladas = false;
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
    semifinalistas.limpiar();
    finalistas.limpiar();
    campeon = 0;
    subcampeon = 0;
    tercerLugar = 0;
    cuartoLugar = 0;
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

Grupo* Torneo::buscarGrupoDeEquipo(Equipo* equipo) const
{
    for (int i = 0; i < grupos.getCantidad(); i++)
    {
        for (int j = 0; j < grupos[i]->getEquipos().getCantidad(); j++)
        {
            if (grupos[i]->getEquipos()[j] == equipo)
            {
                return grupos[i];
            }
        }
    }

    return 0;
}

void Torneo::ordenarEquiposPorDesempeno(Lista<Equipo*>& lista, bool descendente) const
{
    for (int i = 0; i < lista.getCantidad() - 1; i++)
    {
        for (int j = i + 1; j < lista.getCantidad(); j++)
        {
            Grupo* grupoI = buscarGrupoDeEquipo(lista[i]);
            Grupo* grupoJ = buscarGrupoDeEquipo(lista[j]);
            if (grupoI == 0 || grupoJ == 0) continue;

            int puntosI = grupoI->getPuntosDeEquipo(lista[i]);
            int puntosJ = grupoJ->getPuntosDeEquipo(lista[j]);
            int dgI = grupoI->getDiferenciaGolGrupo(lista[i]);
            int dgJ = grupoJ->getDiferenciaGolGrupo(lista[j]);
            int gfI = grupoI->getGolesFavorGrupo(lista[i]);
            int gfJ = grupoJ->getGolesFavorGrupo(lista[j]);

            bool intercambiar = false;

            if (descendente)
            {
                if (puntosJ > puntosI) intercambiar = true;
                else if (puntosJ == puntosI)
                {
                    if (dgJ > dgI) intercambiar = true;
                    else if (dgJ == dgI)
                    {
                        if (gfJ > gfI) intercambiar = true;
                        else if (gfJ == gfI && (rand() % 2) == 1) intercambiar = true;
                    }
                }
            }
            else
            {
                if (puntosJ < puntosI) intercambiar = true;
                else if (puntosJ == puntosI)
                {
                    if (dgJ < dgI) intercambiar = true;
                    else if (dgJ == dgI)
                    {
                        if (gfJ < gfI) intercambiar = true;
                        else if (gfJ == gfI && (rand() % 2) == 1) intercambiar = true;
                    }
                }
            }

            if (intercambiar)
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
    if (lista.estaVacia()) return 0;

    int indice = rand() % lista.getCantidad();
    Equipo* equipo = lista[indice];
    lista.eliminar(indice);
    return equipo;
}

Lista<Equipo*>* Torneo::obtenerBombo(int numeroBombo)
{
    if (numeroBombo == 1) return &bombo1;
    if (numeroBombo == 2) return &bombo2;
    if (numeroBombo == 3) return &bombo3;
    if (numeroBombo == 4) return &bombo4;
    return 0;
}

bool Torneo::mismoGrupo(Equipo* a, Equipo* b) const
{
    if (a == 0 || b == 0) return false;
    return buscarGrupoDeEquipo(a) != 0 && buscarGrupoDeEquipo(a) == buscarGrupoDeEquipo(b);
}

int Torneo::buscarIndiceEquipo(const Lista<Equipo*>& lista, Equipo* equipo) const
{
    for (int i = 0; i < lista.getCantidad(); i++)
    {
        if (lista[i] == equipo) return i;
    }

    return -1;
}

bool Torneo::asignarEquiposAGrupos(int indiceSlot)
{
    const int cantidadGrupos = grupos.getCantidad();
    if (cantidadGrupos == 0) return false;
    if (indiceSlot >= cantidadGrupos * 4) return true;

    int numeroBombo = (indiceSlot / cantidadGrupos) + 1;
    int indiceGrupo = indiceSlot % cantidadGrupos;

    Lista<Equipo*>* bombo = obtenerBombo(numeroBombo);
    if (bombo == 0 || bombo->estaVacia()) return false;

    Grupo* grupo = grupos[indiceGrupo];
    Lista<Equipo*> candidatos = *bombo;

    for (int i = candidatos.getCantidad() - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        Equipo* aux = candidatos[i];
        candidatos[i] = candidatos[j];
        candidatos[j] = aux;
    }

    for (int i = 0; i < candidatos.getCantidad(); i++)
    {
        Equipo* candidato = candidatos[i];
        int indiceCandidato = buscarIndiceEquipo(*bombo, candidato);

        if (indiceCandidato == -1 || !grupo->validarConfederacion(candidato))
        {
            continue;
        }

        bombo->eliminar(indiceCandidato);
        grupo->agregarEquipo(candidato);
        recursos.contarIteracion();

        if (asignarEquiposAGrupos(indiceSlot + 1))
        {
            return true;
        }

        grupo->getEquipos().eliminar(grupo->getEquipos().getCantidad() - 1);
        bombo->agregar(candidato);
    }

    return false;
}

bool Torneo::gruposCompletosYValidos() const
{
    for (int i = 0; i < grupos.getCantidad(); i++)
    {
        const Lista<Equipo*>& equiposGrupo = grupos[i]->getEquipos();
        if (equiposGrupo.getCantidad() != 4)
        {
            return false;
        }

        for (int j = 0; j < equiposGrupo.getCantidad(); j++)
        {
            if (equiposGrupo[j] == 0)
            {
                return false;
            }

            int cantidadMismaConfederacion = 0;
            for (int k = 0; k < equiposGrupo.getCantidad(); k++)
            {
                if (equiposGrupo[k] != 0 &&
                    equiposGrupo[k]->getConfederacion() == equiposGrupo[j]->getConfederacion())
                {
                    cantidadMismaConfederacion++;
                }
            }

            if (equiposGrupo[j]->getConfederacion() == "UEFA")
            {
                if (cantidadMismaConfederacion > 2) return false;
            }
            else if (cantidadMismaConfederacion > 1)
            {
                return false;
            }
        }
    }

    return true;
}

bool Torneo::emparejarDieciseisavos(const Lista<Equipo*>& disponibles, Lista<Equipo*>& cuadro) const
{
    if (disponibles.estaVacia())
    {
        return true;
    }

    Lista<Equipo*> restantes = disponibles;
    Equipo* equipoA = restantes[0];
    restantes.eliminar(0);

    for (int i = 0; i < restantes.getCantidad(); i++)
    {
        Equipo* equipoB = restantes[i];
        if (mismoGrupo(equipoA, equipoB))
        {
            continue;
        }

        Lista<Equipo*> siguientes = restantes;
        siguientes.eliminar(i);
        cuadro.agregar(equipoA);
        cuadro.agregar(equipoB);

        if (emparejarDieciseisavos(siguientes, cuadro))
        {
            return true;
        }

        cuadro.eliminar(cuadro.getCantidad() - 1);
        cuadro.eliminar(cuadro.getCantidad() - 1);
    }

    return false;
}

void Torneo::agregarPareja(Lista<Equipo*>& destino, Equipo* a, Equipo* b)
{
    if (a != 0 && b != 0)
    {
        destino.agregar(a);
        destino.agregar(b);
    }
}

Partido* Torneo::registrarPartido(Equipo* equipo1, Equipo* equipo2, const Fecha& fecha, const string& etapa)
{
    Partido* partido = new Partido(equipo1, equipo2, fecha, etapa);
    partido->configurar(etapa == "GRUPOS" ? "nombreSede" : "Sede_" + etapa, etapa == "GRUPOS" ? "00:00" : "18:00");
    partido->setArbitros("codArbitro1", "codArbitro2", "codArbitro3");
    partidos.agregar(partido);
    return partido;
}

void Torneo::simularRonda(const Lista<Equipo*>& participantes, Lista<Equipo*>& ganadores, const string& etapa, const Fecha& fechaBase, Lista<Equipo*>* perdedores)
{
    ganadores.limpiar();
    if (perdedores != 0) perdedores->limpiar();

    for (int i = 0; i + 1 < participantes.getCantidad(); i += 2)
    {
        Fecha fecha = fechaBase;
        Partido* partido = registrarPartido(participantes[i], participantes[i + 1], fecha, etapa);
        partido->simular();
        ganadores.agregar(partido->getGanador());
        if (perdedores != 0) perdedores->agregar(partido->getPerdedor());
        recursos.contarIteraciones(1);
        cout << *partido << "\n\n";
    }

    actualizarMemoria();
}

long Torneo::estimarMemoriaActual() const
{
    long bytes = sizeof(Torneo);

    bytes += sizeof(Equipo*) * equipos.getCapacidad();
    bytes += sizeof(Equipo*) * bombo1.getCapacidad();
    bytes += sizeof(Equipo*) * bombo2.getCapacidad();
    bytes += sizeof(Equipo*) * bombo3.getCapacidad();
    bytes += sizeof(Equipo*) * bombo4.getCapacidad();
    bytes += sizeof(Grupo*) * grupos.getCapacidad();
    bytes += sizeof(Partido*) * partidos.getCapacidad();

    for (int i = 0; i < equipos.getCantidad(); i++)
    {
        bytes += sizeof(Equipo);
        bytes += sizeof(Jugador*) * equipos[i]->getJugadores().getCapacidad();
        for (int j = 0; j < equipos[i]->getCantidadJugadores(); j++) bytes += sizeof(Jugador);
    }

    for (int i = 0; i < grupos.getCantidad(); i++)
    {
        bytes += sizeof(Grupo);
        bytes += sizeof(Equipo*) * grupos[i]->getEquipos().getCapacidad();
        bytes += sizeof(Partido*) * grupos[i]->getPartidos().getCapacidad();
    }

    for (int i = 0; i < partidos.getCantidad(); i++)
    {
        bytes += sizeof(Partido);
        bytes += sizeof(RegistroJugadorPartido*) * partidos[i]->getConvocadosEquipo1().getCapacidad();
        bytes += sizeof(RegistroJugadorPartido*) * partidos[i]->getConvocadosEquipo2().getCapacidad();
        bytes += sizeof(RegistroJugadorPartido) * partidos[i]->getConvocadosEquipo1().getCantidad();
        bytes += sizeof(RegistroJugadorPartido) * partidos[i]->getConvocadosEquipo2().getCantidad();
    }

    return bytes;
}

void Torneo::actualizarMemoria()
{
    recursos.setBytes(estimarMemoriaActual());
}

int Torneo::indiceConfederacion(const Lista<string>& nombres, const string& confederacion) const
{
    for (int i = 0; i < nombres.getCantidad(); i++)
    {
        if (nombres[i] == confederacion) return i;
    }

    return -1;
}

void Torneo::mostrarConfederacionMayor(const Lista<Equipo*>& lista, const string& etapa, ostream& os) const
{
    Lista<string> nombres;
    Lista<int> cantidades;

    for (int i = 0; i < lista.getCantidad(); i++)
    {
        int indice = indiceConfederacion(nombres, lista[i]->getConfederacion());
        if (indice == -1)
        {
            nombres.agregar(lista[i]->getConfederacion());
            cantidades.agregar(1);
        }
        else
        {
            cantidades[indice]++;
        }
    }

    int mejor = -1;
    for (int i = 0; i < cantidades.getCantidad(); i++)
    {
        if (mejor == -1 || cantidades[i] > cantidades[mejor]) mejor = i;
    }

    if (mejor != -1)
    {
        os << etapa << ": " << nombres[mejor] << " con " << cantidades[mejor] << " equipos\n";
    }
}

void Torneo::agregarEquipo(Equipo* equipo)
{
    if (equipo != 0)
    {
        equipos.agregar(equipo);
        recursos.contarIteracion();
        actualizarMemoria();
    }
}

void Torneo::cargarDatosEquipos(const string& archivo)
{
    liberarTodo();
    recursos.reiniciar();

    ifstream entrada(archivo.c_str());
    if (!entrada.is_open())
    {
        cout << "No se pudo abrir el archivo: " << archivo << "\n";
        return;
    }

    string linea;
    getline(entrada, linea);

    while (getline(entrada, linea))
    {
        if (linea.empty()) continue;

        char separador = ',';
        for (int i = 0; i < static_cast<int>(linea.length()); i++)
        {
            if (linea[i] == ';')
            {
                separador = ';';
                break;
            }
        }

        stringstream ss(linea);
        string pais, director, federacion, confederacion, dato;
        int ranking = 0, gf = 0, gc = 0, pg = 0, pe = 0, pp = 0;

        getline(ss, pais, separador);
        getline(ss, director, separador);
        getline(ss, federacion, separador);
        getline(ss, confederacion, separador);

        getline(ss, dato, separador); if (!dato.empty()) ranking = atoi(dato.c_str());
        getline(ss, dato, separador); if (!dato.empty()) gf = atoi(dato.c_str());
        getline(ss, dato, separador); if (!dato.empty()) gc = atoi(dato.c_str());
        getline(ss, dato, separador); if (!dato.empty()) pg = atoi(dato.c_str());
        getline(ss, dato, separador); if (!dato.empty()) pe = atoi(dato.c_str());
        getline(ss, dato, separador); if (!dato.empty()) pp = atoi(dato.c_str());

        if (!pais.empty())
        {
            agregarEquipo(new Equipo(pais, director, federacion, confederacion, ranking, gf, gc, pg, pe, pp));
        }
    }

    entrada.close();
    datosCargados = equipos.getCantidad() > 0;
    actualizarMemoria();
    cout << "Equipos cargados: " << equipos.getCantidad() << "\n";
    mostrarRecursos(cout);
}

void Torneo::crearJugadoresArtificiales()
{
    if (!datosCargados)
    {
        cout << "Primero debe cargar los equipos.\n";
        return;
    }

    for (int i = 0; i < equipos.getCantidad(); i++)
    {
        Equipo* equipo = equipos[i];

        if (equipo->getCantidadJugadores() > 0) continue;

        for (int j = 1; j <= 26; j++)
        {
            stringstream numero;
            numero << j;
            equipo->agregarJugador(new Jugador("nombre" + numero.str(), "apellido" + numero.str(), j));
            recursos.contarIteracion();
        }

        int golesPorRepartir = equipo->getGolesFavor();
        int indice = 0;
        while (golesPorRepartir > 0 && equipo->getCantidadJugadores() > 0)
        {
            equipo->getJugador(indice)->sumarGol();
            golesPorRepartir--;
            indice = (indice + 1) % equipo->getCantidadJugadores();
            recursos.contarIteracion();
        }
    }

    jugadoresCreados = true;
    actualizarMemoria();
    cout << "Jugadores artificiales creados.\n";
    mostrarRecursos(cout);
}

void Torneo::guardarDatosJugadores(const string& archivo)
{
    ofstream salida(archivo.c_str());
    if (!salida.is_open())
    {
        cout << "No se pudo crear el archivo de jugadores.\n";
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
            recursos.contarIteracion();
        }
    }

    salida.close();
    actualizarMemoria();
    cout << "Datos de jugadores guardados en: " << archivo << "\n";
    mostrarRecursos(cout);
}

void Torneo::crearBombos()
{
    if (!datosCargados)
    {
        cout << "Primero debe cargar los equipos.\n";
        return;
    }

    limpiarBombos();
    Lista<Equipo*> ordenados = equipos;
    ordenarEquiposPorRanking(ordenados);

    int indiceAnfitrion = -1;
    for (int i = 0; i < ordenados.getCantidad(); i++)
    {
        string pais = ordenados[i]->getPais();
        if (pais == "Estados Unidos" || pais == "EE. UU." || pais == "USA" || pais == "United States")
        {
            indiceAnfitrion = i;
            break;
        }
    }

    if (indiceAnfitrion != -1)
    {
        bombo1.agregar(ordenados[indiceAnfitrion]);
        ordenados.eliminar(indiceAnfitrion);
    }

    for (int i = 0; i < ordenados.getCantidad(); i++)
    {
        if (bombo1.getCantidad() < 12) bombo1.agregar(ordenados[i]);
        else if (bombo2.getCantidad() < 12) bombo2.agregar(ordenados[i]);
        else if (bombo3.getCantidad() < 12) bombo3.agregar(ordenados[i]);
        else if (bombo4.getCantidad() < 12) bombo4.agregar(ordenados[i]);
        recursos.contarIteracion();
    }

    bombosCreados = bombo1.getCantidad() > 0 && bombo2.getCantidad() > 0 && bombo3.getCantidad() > 0 && bombo4.getCantidad() > 0;
    actualizarMemoria();

    cout << "Bombos creados.\n";
    cout << "Bombo 1: " << bombo1.getCantidad() << " | Bombo 2: " << bombo2.getCantidad()
              << " | Bombo 3: " << bombo3.getCantidad() << " | Bombo 4: " << bombo4.getCantidad() << "\n";
    mostrarRecursos(cout);
}

Equipo* Torneo::extraerEquipoDeBombo(int numeroBombo)
{
    Lista<Equipo*>* bombo = obtenerBombo(numeroBombo);
    if (bombo == 0) return 0;
    return extraerAleatorioDeLista(*bombo);
}

void Torneo::formarGrupos()
{
    if (!bombosCreados)
    {
        cout << "Primero debe crear los bombos.\n";
        return;
    }

    for (int i = 0; i < grupos.getCantidad(); i++) delete grupos[i];
    grupos.limpiar();

    for (int i = 0; i < 12; i++)
    {
        grupos.agregar(new Grupo(static_cast<char>('A' + i)));
    }

    if (!asignarEquiposAGrupos(0) || !gruposCompletosYValidos())
    {
        gruposFormados = false;
        cout << "No fue posible formar grupos validos con las restricciones de confederacion.\n";
        return;
    }

    gruposFormados = true;
    actualizarMemoria();

    cout << "\nGrupos conformados:\n";
    for (int i = 0; i < grupos.getCantidad(); i++)
    {
        cout << *grupos[i] << "\n";
    }
    mostrarRecursos(cout);
}

void Torneo::configurarPartidosGrupos()
{
    if (!gruposFormados || !gruposCompletosYValidos())
    {
        cout << "Primero debe formar grupos validos.\n";
        return;
    }

    // El patrón de rondas garantiza que cada equipo juegue una vez por ronda.
    // Como se programan 4 partidos por día, los 72 partidos caben en 18 días.
    int combinaciones[6][2] = {{0,1}, {2,3}, {0,2}, {1,3}, {0,3}, {1,2}};
    Fecha inicio(20, 6, 2026);
    int contadorPartidos = 0;

    for (int ronda = 0; ronda < 3; ronda++)
    {
        for (int g = 0; g < grupos.getCantidad(); g++)
        {
            for (int k = 0; k < 2; k++)
            {
                int indiceCombinacion = ronda * 2 + k;
                int a = combinaciones[indiceCombinacion][0];
                int b = combinaciones[indiceCombinacion][1];

                if (grupos[g]->getEquipos().getCantidad() > b)
                {
                    Fecha fecha = inicio;
                    fecha.avanzarDias(contadorPartidos / 4);
                    Partido* partido = registrarPartido(grupos[g]->getEquipos()[a], grupos[g]->getEquipos()[b], fecha, "GRUPOS");
                    grupos[g]->agregarPartido(partido);
                    contadorPartidos++;
                    recursos.contarIteracion();
                }
            }
        }
    }

    partidosGruposConfigurados = true;
    actualizarMemoria();
    cout << "Partidos de grupos configurados: " << contadorPartidos << "\n";
    mostrarRecursos(cout);
}

void Torneo::simularFaseGrupos()
{
    if (!partidosGruposConfigurados)
    {
        cout << "Primero debe configurar los partidos de grupos.\n";
        return;
    }

    for (int i = 0; i < grupos.getCantidad(); i++)
    {
        grupos[i]->simularPartidos();
        grupos[i]->imprimirPartidos(cout);
        grupos[i]->imprimirTabla(cout);
        recursos.contarIteraciones(grupos[i]->getPartidos().getCantidad());
    }

    faseGruposSimulada = true;
    actualizarMemoria();
    mostrarRecursos(cout);
}

void Torneo::clasificarADieciseisavos()
{
    if (!faseGruposSimulada)
    {
        cout << "Primero debe simular la fase de grupos.\n";
        return;
    }

    clasificadosR16.limpiar();
    Lista<Equipo*> primeros;
    Lista<Equipo*> segundos;
    Lista<Equipo*> terceros;

    for (int i = 0; i < grupos.getCantidad(); i++)
    {
        if (grupos[i]->getPrimero() == 0 || grupos[i]->getSegundo() == 0 || grupos[i]->getTercero() == 0)
        {
            clasificadosR16.limpiar();
            cout << "No se pudo clasificar a dieciseisavos porque hay grupos incompletos o invalidos.\n";
            return;
        }
        primeros.agregar(grupos[i]->getPrimero());
        segundos.agregar(grupos[i]->getSegundo());
        terceros.agregar(grupos[i]->getTercero());
    }

    ordenarEquiposPorDesempeno(terceros, true);
    ordenarEquiposPorDesempeno(segundos, false);

    for (int i = 0; i < primeros.getCantidad(); i++) clasificadosR16.agregar(primeros[i]);
    for (int i = 0; i < segundos.getCantidad(); i++) clasificadosR16.agregar(segundos[i]);
    for (int i = 0; i < 8 && i < terceros.getCantidad(); i++) clasificadosR16.agregar(terceros[i]);

    actualizarMemoria();
    cout << "Clasificados a dieciseisavos: " << clasificadosR16.getCantidad() << "\n";
    mostrarRecursos(cout);
}

void Torneo::configurarDieciseisavos()
{
    if (clasificadosR16.getCantidad() < 32)
    {
        clasificarADieciseisavos();
    }

    for (int i = 0; i < clasificadosR16.getCantidad(); i++)
    {
        if (clasificadosR16[i] == 0)
        {
            cout << "No se pueden configurar los dieciseisavos porque la clasificacion es invalida.\n";
            dieciseisavosConfigurados = false;
            return;
        }
    }

    Lista<Equipo*> clasificados = clasificadosR16;
    clasificadosR16.limpiar();
    bool cuadroValido = emparejarDieciseisavos(clasificados, clasificadosR16);

    cuadroValido = cuadroValido && clasificadosR16.getCantidad() == 32;
    for (int i = 0; i < clasificadosR16.getCantidad() && cuadroValido; i++)
    {
        if (clasificadosR16[i] == 0)
        {
            cuadroValido = false;
        }
        else
        {
            for (int j = i + 1; j < clasificadosR16.getCantidad(); j++)
            {
                if (clasificadosR16[i] == clasificadosR16[j])
                {
                    cuadroValido = false;
                    break;
                }
            }
        }
    }

    if (!cuadroValido)
    {
        clasificadosR16.limpiar();
        dieciseisavosConfigurados = false;
        cout << "No se pudo construir un cuadro valido de dieciseisavos.\n";
        return;
    }

    dieciseisavosConfigurados = true;
    actualizarMemoria();

    cout << "\nPartidos configurados para dieciseisavos:\n";
    for (int i = 0; i + 1 < clasificadosR16.getCantidad(); i += 2)
    {
        cout << clasificadosR16[i]->getPais() << " vs " << clasificadosR16[i + 1]->getPais() << "\n";
    }
    mostrarRecursos(cout);
}

void Torneo::simularEliminatorias()
{
    if (!dieciseisavosConfigurados)
    {
        configurarDieciseisavos();
    }

    if (clasificadosR16.getCantidad() < 32)
    {
        cout << "No hay suficientes equipos para simular eliminatorias.\n";
        return;
    }

    Fecha fechaBase(10, 7, 2026);

    cout << "\n===== DIECISEISAVOS =====\n";
    simularRonda(clasificadosR16, clasificadosR8, "DIECISEISAVOS", fechaBase, 0);

    cout << "\n===== OCTAVOS =====\n";
    simularRonda(clasificadosR8, clasificadosR4, "OCTAVOS", fechaBase, 0);

    cout << "\n===== CUARTOS =====\n";
    simularRonda(clasificadosR4, semifinalistas, "CUARTOS", fechaBase, 0);

    Lista<Equipo*> perdedoresSemifinal;
    cout << "\n===== SEMIFINALES =====\n";
    simularRonda(semifinalistas, finalistas, "SEMIFINALES", fechaBase, &perdedoresSemifinal);

    if (perdedoresSemifinal.getCantidad() >= 2)
    {
        cout << "\n===== TERCER PUESTO =====\n";
        Partido* tercerPuesto = registrarPartido(perdedoresSemifinal[0], perdedoresSemifinal[1], fechaBase, "TERCER_PUESTO");
        tercerPuesto->simular();
        tercerLugar = tercerPuesto->getGanador();
        cuartoLugar = tercerPuesto->getPerdedor();
        cout << *tercerPuesto << "\n\n";
    }

    if (finalistas.getCantidad() >= 2)
    {
        cout << "\n===== FINAL =====\n";
        Partido* final = registrarPartido(finalistas[0], finalistas[1], fechaBase, "FINAL");
        final->simular();
        campeon = final->getGanador();
        subcampeon = final->getPerdedor();
        cout << *final << "\n\n";
    }

    eliminatoriasSimuladas = true;
    actualizarMemoria();
    mostrarRecursos(cout);
}

void Torneo::generarEstadisticasFinales(ostream& os) const
{
    os << "\n========== ESTADISTICAS FINALES DEL TORNEO ==========" << "\n";

    os << "\nRanking de los 4 primeros puestos:\n";
    os << "1. " << (campeon != 0 ? campeon->getPais() : "No definido") << "\n";
    os << "2. " << (subcampeon != 0 ? subcampeon->getPais() : "No definido") << "\n";
    os << "3. " << (tercerLugar != 0 ? tercerLugar->getPais() : "No definido") << "\n";
    os << "4. " << (cuartoLugar != 0 ? cuartoLugar->getPais() : "No definido") << "\n";

    os << "\nMaximo goleador del equipo campeon:\n";
    if (campeon != 0)
    {
        Jugador* maximoCampeon = 0;
        for (int i = 0; i < campeon->getCantidadJugadores(); i++)
        {
            Jugador* jugador = campeon->getJugador(i);
            if (maximoCampeon == 0 || maximoCampeon->getGoles() < jugador->getGoles())
            {
                maximoCampeon = jugador;
            }
        }

        if (maximoCampeon != 0)
        {
            os << *maximoCampeon << "\n";
        }
    }
    else
    {
        os << "No definido\n";
    }

    Jugador* top1 = 0;
    Jugador* top2 = 0;
    Jugador* top3 = 0;
    Equipo* equipoTop1 = 0;
    Equipo* equipoTop2 = 0;
    Equipo* equipoTop3 = 0;

    for (int i = 0; i < equipos.getCantidad(); i++)
    {
        for (int j = 0; j < equipos[i]->getCantidadJugadores(); j++)
        {
            Jugador* jugador = equipos[i]->getJugador(j);

            if (top1 == 0 || top1->getGoles() < jugador->getGoles())
            {
                top3 = top2; equipoTop3 = equipoTop2;
                top2 = top1; equipoTop2 = equipoTop1;
                top1 = jugador; equipoTop1 = equipos[i];
            }
            else if (top2 == 0 || top2->getGoles() < jugador->getGoles())
            {
                top3 = top2; equipoTop3 = equipoTop2;
                top2 = jugador; equipoTop2 = equipos[i];
            }
            else if (top3 == 0 || top3->getGoles() < jugador->getGoles())
            {
                top3 = jugador; equipoTop3 = equipos[i];
            }
        }
    }

    os << "\nTres mayores goleadores de toda la copa mundial:\n";
    if (top1 != 0) os << "1. " << top1->getNombre() << " " << top1->getApellido() << " (" << equipoTop1->getPais() << ") - " << top1->getGoles() << " goles\n";
    if (top2 != 0) os << "2. " << top2->getNombre() << " " << top2->getApellido() << " (" << equipoTop2->getPais() << ") - " << top2->getGoles() << " goles\n";
    if (top3 != 0) os << "3. " << top3->getNombre() << " " << top3->getApellido() << " (" << equipoTop3->getPais() << ") - " << top3->getGoles() << " goles\n";

    Equipo* masGolesHistoricos = 0;
    for (int i = 0; i < equipos.getCantidad(); i++)
    {
        if (masGolesHistoricos == 0 || equipos[i]->getGolesFavor() > masGolesHistoricos->getGolesFavor())
        {
            masGolesHistoricos = equipos[i];
        }
    }

    os << "\nEquipo con mas goles historicos actualizados:\n";
    if (masGolesHistoricos != 0)
    {
        os << masGolesHistoricos->getPais() << " con " << masGolesHistoricos->getGolesFavor() << " goles historicos\n";
    }

    os << "\nConfederacion con mayor presencia por etapa:\n";
    mostrarConfederacionMayor(clasificadosR16, "R16 / Dieciseisavos", os);
    mostrarConfederacionMayor(clasificadosR8, "R8 / Octavos", os);
    mostrarConfederacionMayor(clasificadosR4, "R4 / Cuartos", os);
}

void Torneo::mostrarRecursos(ostream& os) const
{
    os << "[Recursos] " << recursos << "\n";
}

void Torneo::menu()
{
    int opcion = -1;
    string archivo;

    while (opcion != 0)
    {
        cout << "\n========== " << nombre << " ==========" << "\n";
        cout << "1. Cargar equipos desde CSV\n";
        cout << "2. Crear jugadores artificiales\n";
        cout << "3. Crear bombos\n";
        cout << "4. Formar grupos\n";
        cout << "5. Configurar partidos de grupos\n";
        cout << "6. Simular fase de grupos\n";
        cout << "7. Clasificar y configurar dieciseisavos\n";
        cout << "8. Simular eliminatorias\n";
        cout << "9. Mostrar estadisticas finales\n";
        cout << "10. Guardar datos de jugadores\n";
        cout << "11. Mostrar recursos\n";
        cout << "12. Ejecutar flujo completo\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 1)
        {
            cout << "Ruta del CSV: ";
            cin >> archivo;
            cargarDatosEquipos(archivo);
        }
        else if (opcion == 2) crearJugadoresArtificiales();
        else if (opcion == 3) crearBombos();
        else if (opcion == 4) formarGrupos();
        else if (opcion == 5) configurarPartidosGrupos();
        else if (opcion == 6) simularFaseGrupos();
        else if (opcion == 7)
        {
            clasificarADieciseisavos();
            configurarDieciseisavos();
        }
        else if (opcion == 8) simularEliminatorias();
        else if (opcion == 9) generarEstadisticasFinales(cout);
        else if (opcion == 10)
        {
            cout << "Archivo de salida: ";
            cin >> archivo;
            guardarDatosJugadores(archivo);
        }
        else if (opcion == 11) mostrarRecursos(cout);
        else if (opcion == 12)
        {
            cout << "Ruta del CSV: ";
            cin >> archivo;
            cargarDatosEquipos(archivo);
            crearJugadoresArtificiales();
            crearBombos();
            formarGrupos();
            configurarPartidosGrupos();
            simularFaseGrupos();
            clasificarADieciseisavos();
            configurarDieciseisavos();
            simularEliminatorias();
            generarEstadisticasFinales(cout);
            guardarDatosJugadores("jugadores_actualizados.csv");
        }
    }
}

const Lista<Equipo*>& Torneo::getEquipos() const { return equipos; }
const Lista<Grupo*>& Torneo::getGrupos() const { return grupos; }
const Lista<Partido*>& Torneo::getPartidos() const { return partidos; }
const Lista<Equipo*>& Torneo::getClasificadosR16() const { return clasificadosR16; }
const Lista<Equipo*>& Torneo::getClasificadosR8() const { return clasificadosR8; }
const Lista<Equipo*>& Torneo::getClasificadosR4() const { return clasificadosR4; }
Recursos& Torneo::getRecursos() { return recursos; }
const Recursos& Torneo::getRecursos() const { return recursos; }

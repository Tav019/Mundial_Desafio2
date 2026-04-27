#include "torneo.h"

using namespace std;

#include <cstdlib>
#include <ctime>
#include <fstream>

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

Torneo::Torneo(const string& _nombre)
{
    nombre = _nombre;
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
    int cantidad = lista.getCantidad();
    if (cantidad < 2)
    {
        return;
    }

    Grupo** gruposPorEquipo = new Grupo*[cantidad];
    int* puntos = new int[cantidad];
    int* diferencias = new int[cantidad];
    int* golesFavor = new int[cantidad];

    for (int i = 0; i < cantidad; i++)
    {
        gruposPorEquipo[i] = buscarGrupoDeEquipo(lista[i]);

        if (gruposPorEquipo[i] == 0)
        {
            puntos[i] = 0;
            diferencias[i] = 0;
            golesFavor[i] = 0;
            continue;
        }

        puntos[i] = gruposPorEquipo[i]->getPuntosDeEquipo(lista[i]);
        diferencias[i] = gruposPorEquipo[i]->getDiferenciaGolGrupo(lista[i]);
        golesFavor[i] = gruposPorEquipo[i]->getGolesFavorGrupo(lista[i]);
    }

    for (int i = 0; i < lista.getCantidad() - 1; i++)
    {
        for (int j = i + 1; j < lista.getCantidad(); j++)
        {
            Grupo* grupoI = gruposPorEquipo[i];
            Grupo* grupoJ = gruposPorEquipo[j];
            if (grupoI == 0 || grupoJ == 0) continue;

            int puntosI = puntos[i];
            int puntosJ = puntos[j];
            int dgI = diferencias[i];
            int dgJ = diferencias[j];
            int gfI = golesFavor[i];
            int gfJ = golesFavor[j];

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

                Grupo* auxGrupo = gruposPorEquipo[i];
                gruposPorEquipo[i] = gruposPorEquipo[j];
                gruposPorEquipo[j] = auxGrupo;

                int auxPuntos = puntos[i];
                puntos[i] = puntos[j];
                puntos[j] = auxPuntos;

                int auxDiferencia = diferencias[i];
                diferencias[i] = diferencias[j];
                diferencias[j] = auxDiferencia;

                int auxGolesFavor = golesFavor[i];
                golesFavor[i] = golesFavor[j];
                golesFavor[j] = auxGolesFavor;
            }
        }
    }

    delete[] gruposPorEquipo;
    delete[] puntos;
    delete[] diferencias;
    delete[] golesFavor;
}

bool Torneo::mismoGrupo(Equipo* a, Equipo* b) const
{
    if (a == 0 || b == 0) return false;
    return buscarGrupoDeEquipo(a) != 0 && buscarGrupoDeEquipo(a) == buscarGrupoDeEquipo(b);
}

bool Torneo::emparejarDieciseisavosPorBloques(const Lista<Equipo*>& primeros, const Lista<Equipo*>& segundosDisponibles,
    const Lista<Equipo*>& tercerosDisponibles, int indicePrimero, int cantidadPrimerosVsTerceros, Lista<Equipo*>& cuadro) const
{
    if (indicePrimero >= primeros.getCantidad())
    {
        return emparejarDieciseisavos(segundosDisponibles, cuadro);
    }

    Equipo* equipoA = primeros[indicePrimero];

    if (indicePrimero < cantidadPrimerosVsTerceros)
    {
        for (int i = 0; i < tercerosDisponibles.getCantidad(); i++)
        {
            Equipo* equipoB = tercerosDisponibles[i];
            if (mismoGrupo(equipoA, equipoB))
            {
                continue;
            }

            Lista<Equipo*> siguientesTerceros = tercerosDisponibles;
            siguientesTerceros.eliminar(i);
            cuadro.agregar(equipoA);
            cuadro.agregar(equipoB);

            if (emparejarDieciseisavosPorBloques(primeros, segundosDisponibles, siguientesTerceros,indicePrimero + 1,
            cantidadPrimerosVsTerceros, cuadro))
            {
                return true;
            }

            cuadro.eliminar(cuadro.getCantidad() - 1);
            cuadro.eliminar(cuadro.getCantidad() - 1);
        }

        return false;
    }

    for (int i = 0; i < segundosDisponibles.getCantidad(); i++)
    {
        Equipo* equipoB = segundosDisponibles[i];
        if (mismoGrupo(equipoA, equipoB))
        {
            continue;
        }

        Lista<Equipo*> siguientesSegundos = segundosDisponibles;
        siguientesSegundos.eliminar(i);
        cuadro.agregar(equipoA);
        cuadro.agregar(equipoB);

        if (emparejarDieciseisavosPorBloques(primeros, siguientesSegundos, tercerosDisponibles,indicePrimero + 1,
        cantidadPrimerosVsTerceros, cuadro))
        {
            return true;
        }

        cuadro.eliminar(cuadro.getCantidad() - 1);
        cuadro.eliminar(cuadro.getCantidad() - 1);
    }

    return false;
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
        partido->liberarDetalleSimulacion();
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

    if (!OrganizadorTorneo::cargarEquiposDesdeCSV(archivo, equipos))
    {
        cout << "No se pudo abrir el archivo: " << archivo << "\n";
        return;
    }
    recursos.contarIteraciones(equipos.getCantidad());
    datosCargados = equipos.getCantidad() > 0;
    equipos.compactar();
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
            string numero = to_string(j);
            equipo->agregarJugador(new Jugador("nombre" + numero, "apellido" + numero, j));
        }

        int cantidadJugadores = equipo->getCantidadJugadores();
        int golesPorRepartir = equipo->getGolesFavor();
        if (cantidadJugadores > 0)
        {
            int baseGolesPorJugador = golesPorRepartir / cantidadJugadores;
            int golesExtra = golesPorRepartir % cantidadJugadores;

            for (int j = 0; j < cantidadJugadores; j++)
            {
                int golesJugador = baseGolesPorJugador + (j < golesExtra ? 1 : 0);
                equipo->getJugador(j)->setGoles(golesJugador);
            }
        }

        recursos.contarIteracion();
        equipo->getJugadores().compactar();
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

void Torneo::guardarDatosHistoricosEquipos(const string& archivo)
{
    ofstream salida(archivo.c_str());
    if (!salida.is_open())
    {
        cout << "No se pudo crear el archivo historico de equipos.\n";
        return;
    }

    salida << "Ranking FIFA,País,Director técnico,Federación de fútbol,Confederación,Goles a favor,Goles en contra,Partidos ganados,Partidos empatados,Partidos perdidos\n";

    for (int i = 0; i < equipos.getCantidad(); i++)
    {
        Equipo* equipo = equipos[i];
        salida << equipo->getRankingFIFA() << ","
               << equipo->getPais() << ","
               << equipo->getDirectorTecnico() << ","
               << equipo->getFederacion() << ","
               << equipo->getConfederacion() << ","
               << equipo->getGolesFavor() << ","
               << equipo->getGolesContra() << ","
               << equipo->getPartidosGanados() << ","
               << equipo->getPartidosEmpatados() << ","
               << equipo->getPartidosPerdidos() << "\n";
        recursos.contarIteracion();
    }

    salida.close();
    actualizarMemoria();
    cout << "Historico de equipos guardado en: " << archivo << "\n";
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
    OrganizadorTorneo::crearBombos(equipos, bombo1, bombo2, bombo3, bombo4);
    recursos.contarIteraciones(equipos.getCantidad());

    bombosCreados = bombo1.getCantidad() > 0 && bombo2.getCantidad() > 0 && bombo3.getCantidad() > 0 && bombo4.getCantidad() > 0;
    bombo1.compactar();
    bombo2.compactar();
    bombo3.compactar();
    bombo4.compactar();
    actualizarMemoria();

    cout << "Bombos creados.\n";
    cout << "Bombo 1: " << bombo1.getCantidad() << " | Bombo 2: " << bombo2.getCantidad()
              << " | Bombo 3: " << bombo3.getCantidad() << " | Bombo 4: " << bombo4.getCantidad() << "\n";
    mostrarRecursos(cout);
}

Equipo* Torneo::extraerEquipoDeBombo(int numeroBombo)
{
    Lista<Equipo*>* bombo = 0;
    if (numeroBombo == 1) bombo = &bombo1;
    else if (numeroBombo == 2) bombo = &bombo2;
    else if (numeroBombo == 3) bombo = &bombo3;
    else if (numeroBombo == 4) bombo = &bombo4;
    if (bombo == 0) return 0;
    if (bombo->estaVacia()) return 0;

    int indice = rand() % bombo->getCantidad();
    Equipo* equipo = (*bombo)[indice];
    bombo->eliminar(indice);
    return equipo;
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

    if (!OrganizadorTorneo::formarGrupos(grupos, bombo1, bombo2, bombo3, bombo4, recursos) ||
        !OrganizadorTorneo::gruposCompletosYValidos(grupos))
    {
        gruposFormados = false;
        cout << "No fue posible formar grupos validos con las restricciones de confederacion.\n";
        return;
    }

    gruposFormados = true;
    recursos.contarIteraciones(grupos.getCantidad() * 4);
    grupos.compactar();
    for (int i = 0; i < grupos.getCantidad(); i++)
    {
        grupos[i]->getEquipos().compactar();
    }
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
    if (!gruposFormados || !OrganizadorTorneo::gruposCompletosYValidos(grupos))
    {
        cout << "Primero debe formar grupos validos.\n";
        return;
    }



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
                }
            }
        }
    }

    partidosGruposConfigurados = true;
    recursos.contarIteraciones(contadorPartidos);
    for (int i = 0; i < grupos.getCantidad(); i++)
    {
        grupos[i]->getPartidos().compactar();
    }
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
        for (int j = 0; j < grupos[i]->getPartidos().getCantidad(); j++)
        {
            grupos[i]->getPartidos()[j]->liberarDetalleSimulacion();
        }
    }

    faseGruposSimulada = true;
    recursos.contarIteraciones(grupos.getCantidad());
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
        Lista<Equipo*> ordenGrupo = grupos[i]->ordenarEquipos();
        if (ordenGrupo.getCantidad() < 3 || ordenGrupo[0] == 0 || ordenGrupo[1] == 0 || ordenGrupo[2] == 0)
        {
            clasificadosR16.limpiar();
            cout << "No se pudo clasificar a dieciseisavos porque hay grupos incompletos o invalidos.\n";
            return;
        }
        primeros.agregar(ordenGrupo[0]);
        segundos.agregar(ordenGrupo[1]);
        terceros.agregar(ordenGrupo[2]);
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
    Lista<Equipo*> primeros;
    Lista<Equipo*> segundos;
    Lista<Equipo*> terceros;

    for (int i = 0; i < grupos.getCantidad() && i < clasificados.getCantidad(); i++)
    {
        primeros.agregar(clasificados[i]);
    }

    for (int i = grupos.getCantidad(); i < grupos.getCantidad() * 2 && i < clasificados.getCantidad(); i++)
    {
        segundos.agregar(clasificados[i]);
    }

    for (int i = grupos.getCantidad() * 2; i < clasificados.getCantidad(); i++)
    {
        terceros.agregar(clasificados[i]);
    }

    clasificadosR16.limpiar();
    bool cuadroValido = emparejarDieciseisavosPorBloques(primeros, segundos, terceros, 0, terceros.getCantidad(), clasificadosR16);

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
        cout << "11. Guardar historico de equipos\n";
        cout << "12. Mostrar recursos\n";
        cout << "13. Ejecutar flujo completo\n";
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
        else if (opcion == 11)
        {
            cout << "Archivo historico de equipos: ";
            cin >> archivo;
            guardarDatosHistoricosEquipos(archivo);
        }
        else if (opcion == 12) mostrarRecursos(cout);
        else if (opcion == 13)
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
            guardarDatosHistoricosEquipos("selecciones_clasificadas_mundial_actualizado.csv");
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

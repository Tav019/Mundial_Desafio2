#include <iostream>
#include <string>
#include "torneo.h"

using namespace std;

int main()
{
    string archivoEntrada = "selecciones_clasificadas_mundial.csv";

    Torneo mundial("UdeAWorldCup");

    cout << "========== INICIO DE SIMULACION UdeAWorldCup ==========\n\n";

    mundial.cargarDatosEquipos(archivoEntrada);
    mundial.crearJugadoresArtificiales();

    mundial.crearBombos();
    mundial.formarGrupos();

    mundial.configurarPartidosGrupos();
    mundial.simularFaseGrupos();

    mundial.clasificarADieciseisavos();
    mundial.configurarDieciseisavos();

    mundial.simularEliminatorias();

    mundial.generarEstadisticasFinales(cout);

    mundial.guardarDatosJugadores("jugadores_actualizados.csv");
    mundial.guardarDatosHistoricosEquipos("selecciones_clasificadas_mundial_actualizado.csv");

    mundial.mostrarRecursos(cout);

    cout << "\n========== FIN DE SIMULACION ==========\n";

    return 0;
}

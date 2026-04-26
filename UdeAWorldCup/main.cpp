#include <iostream>
#include <string>
#include "torneo.h"

using namespace std;

int main(int argc, char* argv[])
{
    string archivoEntrada = "selecciones_clasificadas_mundial.csv";

    if (argc > 1)
    {
        archivoEntrada = argv[1];
    }

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

    mundial.mostrarRecursos(cout);

    cout << "\n========== FIN DE SIMULACION ==========\n";

    return 0;
}

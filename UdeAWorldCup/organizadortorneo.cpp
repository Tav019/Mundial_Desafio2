#include "organizadortorneo.h"

#include <cstdlib>
#include <fstream>
#include <cctype>

static string extraerCampo(string linea, int& inicio, char separador)
{
    int fin = inicio;
    while (fin < static_cast<int>(linea.length()) && linea[fin] != separador)
    {
        fin++;
    }

    string campo = linea.substr(inicio, fin - inicio);
    inicio = fin + 1;
    return campo;
}

static bool empiezaConNumero(const string& texto)
{
    return !texto.empty() && isdigit((unsigned char)texto[0]) != 0;
}

static int contarCandidatosValidos(Grupo* grupo, const Lista<Equipo*>& bombo)
{
    if (grupo == 0)
    {
        return 0;
    }

    int cantidad = 0;
    for (int i = 0; i < bombo.getCantidad(); i++)
    {
        if (grupo->validarConfederacion(bombo[i]))
        {
            cantidad++;
        }
    }

    return cantidad;
}

void OrganizadorTorneo::ordenarEquiposPorRanking(Lista<Equipo*>& lista)
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

Lista<Equipo*>* OrganizadorTorneo::obtenerBombo(int numeroBombo, Lista<Equipo*>& bombo1,Lista<Equipo*>& bombo2,
    Lista<Equipo*>& bombo3, Lista<Equipo*>& bombo4)
{
    if (numeroBombo == 1)
        return &bombo1;
    if (numeroBombo == 2)
        return &bombo2;
    if (numeroBombo == 3)
        return &bombo3;
    if (numeroBombo == 4)
        return &bombo4;
    return 0;
}

int OrganizadorTorneo::buscarIndiceEquipo(Lista<Equipo*>& lista, Equipo* equipo)
{
    for (int i = 0; i < lista.getCantidad(); i++)
    {
        if (lista[i] == equipo) return i;
    }

    return -1;
}

bool OrganizadorTorneo::asignarEquiposAGrupos(Lista<Grupo*>& grupos,Lista<Equipo*>& bombo1,Lista<Equipo*>& bombo2,
                                              Lista<Equipo*>& bombo3, Lista<Equipo*>& bombo4,int indiceSlot, Recursos& recursos)
{
    const int cantidadGrupos = grupos.getCantidad();
    if (cantidadGrupos == 0) return false;
    if (indiceSlot >= cantidadGrupos * 4) return true;

    int numeroBombo = (indiceSlot / cantidadGrupos) + 1;
    int indiceGrupo = indiceSlot % cantidadGrupos;

    Lista<Equipo*>* bombo = obtenerBombo(numeroBombo, bombo1, bombo2, bombo3, bombo4);
    if (bombo == 0 || bombo->estaVacia()) return false;

    int mejorIndiceGrupo = -1;
    int menorCantidadCandidatos = bombo->getCantidad() + 1;

    for (int i = 0; i < cantidadGrupos; i++)
    {
        Grupo* grupoActual = grupos[i];
        if (grupoActual == 0 || grupoActual->getEquipos().getCantidad() != numeroBombo - 1)
        {
            continue;
        }

        int candidatosValidos = contarCandidatosValidos(grupoActual, *bombo);
        if (candidatosValidos == 0)
        {
            return false;
        }

        if (mejorIndiceGrupo == -1 || candidatosValidos < menorCantidadCandidatos)
        {
            mejorIndiceGrupo = i;
            menorCantidadCandidatos = candidatosValidos;
        }
    }

    if (mejorIndiceGrupo == -1)
    {
        mejorIndiceGrupo = indiceGrupo;
    }

    Grupo* grupo = grupos[mejorIndiceGrupo];
    int cantidadCandidatos = bombo->getCantidad();
    Equipo** candidatos = new Equipo*[cantidadCandidatos];

    for (int i = 0; i < cantidadCandidatos; i++)
    {
        candidatos[i] = (*bombo)[i];
    }

    for (int i = cantidadCandidatos - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        Equipo* aux = candidatos[i];
        candidatos[i] = candidatos[j];
        candidatos[j] = aux;
    }

    for (int i = 0; i < cantidadCandidatos; i++)
    {
        Equipo* candidato = candidatos[i];
        int indiceCandidato = buscarIndiceEquipo(*bombo, candidato);

        if (indiceCandidato == -1 || !grupo->validarConfederacion(candidato))
        {
            continue;
        }

        bombo->eliminar(indiceCandidato);
        grupo->agregarEquipo(candidato);

        if (asignarEquiposAGrupos(grupos, bombo1, bombo2, bombo3, bombo4, indiceSlot + 1, recursos))
        {
            delete[] candidatos;
            return true;
        }

        grupo->getEquipos().eliminar(grupo->getEquipos().getCantidad() - 1);
        bombo->agregar(candidato);
    }

    delete[] candidatos;
    return false;
}

bool OrganizadorTorneo::cargarEquiposDesdeCSV(const string& archivo, Lista<Equipo*>& equipos)
{
    ifstream entrada(archivo.c_str());
    if (!entrada.is_open())
    {
        return false;
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

        int inicio = 0;

        string campos[10];
        for (int i = 0; i < 10; i++)
        {
            campos[i] = extraerCampo(linea, inicio, separador);
        }

        if (!empiezaConNumero(campos[0]) && !empiezaConNumero(campos[4]))
        {
            continue;
        }

        string pais;
        string director;
        string federacion;
        string confederacion;
        int ranking = 0;
        int gf = 0;
        int gc = 0;
        int pg = 0;
        int pe = 0;
        int pp = 0;

        if (empiezaConNumero(campos[0]))
        {
            ranking = atoi(campos[0].c_str());
            pais = campos[1];
            director = campos[2];
            federacion = campos[3];
            confederacion = campos[4];
            if (!campos[5].empty()) gf = atoi(campos[5].c_str());
            if (!campos[6].empty()) gc = atoi(campos[6].c_str());
            if (!campos[7].empty()) pg = atoi(campos[7].c_str());
            if (!campos[8].empty()) pe = atoi(campos[8].c_str());
            if (!campos[9].empty()) pp = atoi(campos[9].c_str());
        }
        else
        {
            pais = campos[0];
            director = campos[1];
            federacion = campos[2];
            confederacion = campos[3];
            if (!campos[4].empty()) ranking = atoi(campos[4].c_str());
            if (!campos[5].empty()) gf = atoi(campos[5].c_str());
            if (!campos[6].empty()) gc = atoi(campos[6].c_str());
            if (!campos[7].empty()) pg = atoi(campos[7].c_str());
            if (!campos[8].empty()) pe = atoi(campos[8].c_str());
            if (!campos[9].empty()) pp = atoi(campos[9].c_str());
        }

        if (!pais.empty() && !confederacion.empty())
        {
            equipos.agregar(new Equipo(pais, director, federacion, confederacion, ranking, gf, gc, pg, pe, pp));
        }
    }

    entrada.close();
    return true;
}

void OrganizadorTorneo::crearBombos(Lista<Equipo*>& equipos, Lista<Equipo*>& bombo1,Lista<Equipo*>& bombo2,
    Lista<Equipo*>& bombo3,Lista<Equipo*>& bombo4)
{
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
        if (bombo1.getCantidad() < 12)
            bombo1.agregar(ordenados[i]);
        else if (bombo2.getCantidad() < 12)
            bombo2.agregar(ordenados[i]);
        else if (bombo3.getCantidad() < 12)
            bombo3.agregar(ordenados[i]);
        else if (bombo4.getCantidad() < 12)
            bombo4.agregar(ordenados[i]);
    }
}

bool OrganizadorTorneo::gruposCompletosYValidos(Lista<Grupo*>& grupos)
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

bool OrganizadorTorneo::formarGrupos(Lista<Grupo*>& grupos,Lista<Equipo*>& bombo1,Lista<Equipo*>& bombo2,
    Lista<Equipo*>& bombo3,Lista<Equipo*>& bombo4,Recursos& recursos)
{
    return asignarEquiposAGrupos(grupos, bombo1, bombo2, bombo3, bombo4, 0, recursos);
}

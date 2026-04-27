#include "Lista.h"

#include <string>

class Equipo;
class Jugador;
class Grupo;
class Partido;
class RegistroJugadorPartido;

template <class T>
void Lista<T>::redimensionar()
{
    int nuevaCapacidad = capacidad * 2;
    T* nuevosDatos = new T[nuevaCapacidad];

    for (int i = 0; i < cantidad; i++)
    {
        nuevosDatos[i] = datos[i];
    }

    delete[] datos;
    datos = nuevosDatos;
    capacidad = nuevaCapacidad;
}

template <class T>
Lista<T>::Lista()
{
    cantidad = 0;
    capacidad = 10;
    datos = new T[capacidad];
}

template <class T>
Lista<T>::Lista(const Lista<T>& otra)
{
    cantidad = otra.cantidad;
    capacidad = otra.capacidad;
    datos = new T[capacidad];

    for (int i = 0; i < cantidad; i++)
    {
        datos[i] = otra.datos[i];
    }
}

template <class T>
Lista<T>::~Lista()
{
    delete[] datos;
}

template <class T>
Lista<T>& Lista<T>::operator=(const Lista<T>& otra)
{
    if (this != &otra)
    {
        delete[] datos;
        cantidad = otra.cantidad;
        capacidad = otra.capacidad;
        datos = new T[capacidad];

        for (int i = 0; i < cantidad; i++)
        {
            datos[i] = otra.datos[i];
        }
    }

    return *this;
}

template <class T>
void Lista<T>::agregar(const T& elemento)
{
    if (cantidad == capacidad)
    {
        redimensionar();
    }

    datos[cantidad] = elemento;
    cantidad++;
}

template <class T>
void Lista<T>::eliminar(int posicion)
{
    if (posicion < 0 || posicion >= cantidad)
    {
        return;
    }

    for (int i = posicion; i < cantidad - 1; i++)
    {
        datos[i] = datos[i + 1];
    }

    cantidad--;
}

template <class T>
T Lista<T>::obtener(int posicion) const
{
    if (posicion < 0 || posicion >= cantidad)
    {
        return T();
    }

    return datos[posicion];
}

template <class T>
int Lista<T>::getCantidad() const
{
    return cantidad;
}

template <class T>
int Lista<T>::getTamano() const
{
    return cantidad;
}

template <class T>
int Lista<T>::getCapacidad() const
{
    return capacidad;
}

template <class T>
bool Lista<T>::estaVacia() const
{
    return cantidad == 0;
}

template <class T>
void Lista<T>::limpiar()
{
    cantidad = 0;
}

template <class T>
void Lista<T>::compactar()
{
    int nuevaCapacidad = cantidad > 0 ? cantidad : 1;

    if (nuevaCapacidad == capacidad)
    {
        return;
    }

    T* nuevosDatos = new T[nuevaCapacidad];

    for (int i = 0; i < cantidad; i++)
    {
        nuevosDatos[i] = datos[i];
    }

    delete[] datos;
    datos = nuevosDatos;
    capacidad = nuevaCapacidad;
}

template <class T>
T& Lista<T>::operator[](int posicion)
{
    return datos[posicion];
}

template <class T>
const T& Lista<T>::operator[](int posicion) const
{
    return datos[posicion];
}

template class Lista<Equipo*>;
template class Lista<Jugador*>;
template class Lista<Grupo*>;
template class Lista<Partido*>;
template class Lista<RegistroJugadorPartido*>;
template class Lista<std::string>;
template class Lista<int>;

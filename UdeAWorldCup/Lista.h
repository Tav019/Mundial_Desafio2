#ifndef LISTA_H
#define LISTA_H

template <class T>
class Lista
{
private:
    T* datos;
    int cantidad;
    int capacidad;

    void redimensionar()
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

public:
    Lista()
    {
        cantidad = 0;
        capacidad = 10;
        datos = new T[capacidad];
    }

    Lista(const Lista<T>& otra)
    {
        cantidad = otra.cantidad;
        capacidad = otra.capacidad;
        datos = new T[capacidad];

        for (int i = 0; i < cantidad; i++)
        {
            datos[i] = otra.datos[i];
        }
    }

    ~Lista()
    {
        delete[] datos;
    }

    Lista<T>& operator=(const Lista<T>& otra)
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

    void agregar(const T& elemento)
    {
        if (cantidad == capacidad)
        {
            redimensionar();
        }

        datos[cantidad] = elemento;
        cantidad++;
    }

    void eliminar(int posicion)
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

    T obtener(int posicion) const
    {
        if (posicion < 0 || posicion >= cantidad)
        {
            return T();
        }

        return datos[posicion];
    }

    int getCantidad() const
    {
        return cantidad;
    }

    int getTamano() const
    {
        return cantidad;
    }

    int getCapacidad() const
    {
        return capacidad;
    }

    bool estaVacia() const
    {
        return cantidad == 0;
    }

    bool vacia() const
    {
        return estaVacia();
    }

    void limpiar()
    {
        cantidad = 0;
    }

    T& operator[](int posicion)
    {
        return datos[posicion];
    }

    const T& operator[](int posicion) const
    {
        return datos[posicion];
    }
};

#endif

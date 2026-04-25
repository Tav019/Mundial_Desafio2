#ifndef LISTA_H
#define LISTA_H

template <class T>
class Lista
{
private:
    // La lista usa un arreglo dinámico propio para cumplir la restricción de no usar STL.
    T* datos;
    int cantidad;
    int capacidad;

    void redimensionar()
    {
        // Se duplica la capacidad para no reservar memoria en cada inserción.
        capacidad *= 2;
        T* nuevosDatos = new T[capacidad];

        for (int i = 0; i < cantidad; i++)
        {
            nuevosDatos[i] = datos[i];
        }

        delete[] datos;
        datos = nuevosDatos;
    }

public:
    Lista()
    {
        capacidad = 10;
        cantidad = 0;
        datos = new T[capacidad];
    }

    Lista(const Lista<T>& otra)
    {
        capacidad = otra.capacidad;
        cantidad = otra.cantidad;
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

            capacidad = otra.capacidad;
            cantidad = otra.cantidad;
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

    void eliminar(int pos)
    {
        if (pos < 0 || pos >= cantidad)
        {
            return;
        }

        for (int i = pos; i < cantidad - 1; i++)
        {
            datos[i] = datos[i + 1];
        }

        cantidad--;
    }

    T obtener(int pos) const
    {
        if (pos < 0 || pos >= cantidad)
        {
            return T();
        }

        return datos[pos];
    }

    int getCantidad() const
    {
        return cantidad;
    }

    int getTamano() const
    {
        return cantidad;
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

    T& operator[](int pos)
    {
        return datos[pos];
    }

    const T& operator[](int pos) const
    {
        return datos[pos];
    }
};

#endif

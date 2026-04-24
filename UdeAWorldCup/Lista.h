#ifndef LISTA_H
#define LISTA_H

template <class T>
class Lista
{
private:
    T* datos;
    int tamano;
    int capacidad;

    void redimensionar()
    {
        capacidad = capacidad * 2;
        T* nuevo = new T[capacidad];

        for (int i = 0; i < tamano; i++)
        {
            nuevo[i] = datos[i];
        }

        delete[] datos;
        datos = nuevo;
    }

public:
    Lista()
    {
        capacidad = 10;
        tamano = 0;
        datos = new T[capacidad];
    }

    Lista(const Lista<T>& otra)
    {
        capacidad = otra.capacidad;
        tamano = otra.tamano;
        datos = new T[capacidad];

        for (int i = 0; i < tamano; i++)
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
            tamano = otra.tamano;
            datos = new T[capacidad];

            for (int i = 0; i < tamano; i++)
            {
                datos[i] = otra.datos[i];
            }
        }

        return *this;
    }

    void agregar(const T& valor)
    {
        if (tamano == capacidad)
        {
            redimensionar();
        }

        datos[tamano] = valor;
        tamano++;
    }

    void eliminar(int indice)
    {
        if (indice < 0 || indice >= tamano)
        {
            return;
        }

        for (int i = indice; i < tamano - 1; i++)
        {
            datos[i] = datos[i + 1];
        }

        tamano--;
    }

    T& operator[](int indice)
    {
        return datos[indice];
    }

    const T& operator[](int indice) const
    {
        return datos[indice];
    }

    int getTamano() const
    {
        return tamano;
    }

    bool vacia() const
    {
        return tamano == 0;
    }
};

#endif

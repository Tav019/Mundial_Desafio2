#ifndef LISTA_H
#define LISTA_H

template <class T>
class Lista
{
private:
    T* datos;
    int cantidad;
    int capacidad;

    void redimensionar();

public:
    Lista();
    Lista(const Lista<T>& otra);
    ~Lista();

    Lista<T>& operator=(const Lista<T>& otra);

    void agregar(const T& elemento);
    void eliminar(int posicion);
    T obtener(int posicion) const;
    int getCantidad() const;
    int getTamano() const;
    int getCapacidad() const;
    bool estaVacia() const;
    void limpiar();
    void compactar();
    T& operator[](int posicion);
    const T& operator[](int posicion) const;
};

#endif

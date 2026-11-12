/*
 * Curso     : Programacion Orientada a Objetos en C++
 * Actividad : Evaluacion 3 - Proyecto Integrador SMTI (Unidad 9: Sockets)
 * Docente   : Ing. Paola Andrea Bedoya Toro
 * Estudiantes: Arturo Ortiz y Sergio David Castillo
 * Archivo   : ListaGen.h
 */
#ifndef LISTAGEN_H
#define LISTAGEN_H

#include <iostream>
#include <stdexcept>

template <typename T>
struct NodoGen {
    T dato;
    NodoGen<T>* siguiente;
    NodoGen(T _d) : dato(_d), siguiente(nullptr) {}
};

// Lista enlazada generica. Esta version esta pensada para T = puntero a objeto
// en el Heap (ej. Sensor*): la lista es DUENA de los objetos y los libera.
template <typename T>
class ListaGen {
private:
    NodoGen<T>* head;
    int tamanio;

public:
    ListaGen() : head(nullptr), tamanio(0) {}

    // Una lista duena de punteros NO se puede copiar (doble delete).
    ListaGen(const ListaGen&) = delete;
    ListaGen& operator=(const ListaGen&) = delete;

    // Destructor generico: purga total del Heap
    ~ListaGen() {
        NodoGen<T>* actual = head;
        while (actual != nullptr) {
            NodoGen<T>* aux = actual->siguiente; // guardar ANTES de borrar el nodo
            delete actual->dato;                 // 1) liberar el objeto apuntado (ej. SensorTemperatura)
            delete actual;                       // 2) liberar el nodo
            actual = aux;
        }
        head = nullptr;
        tamanio = 0;
    }

    // Insercion al inicio: O(1)
    void insertar(T nuevoDato) {
        NodoGen<T>* nuevo = new NodoGen<T>(nuevoDato);
        nuevo->siguiente = head;
        head = nuevo;
        ++tamanio;
    }

    // Recorrido polimorfico: dato->procesarLectura() usa la vtable (dynamic binding)
    void procesarTodo() {
        NodoGen<T>* actual = head;
        while (actual != nullptr) {
            actual->dato->procesarLectura();
            actual = actual->siguiente;
        }
    }

    // Busqueda por ID (devuelve nullptr si no existe)
    T buscarPorId(int id) const {
        NodoGen<T>* actual = head;
        while (actual != nullptr) {
            if (actual->dato->getId() == id) return actual->dato;
            actual = actual->siguiente;
        }
        return nullptr;
    }

    int getTamanio() const { return tamanio; }
};

#endif

/*
 * Curso     : Programacion Orientada a Objetos en C++
 * Actividad : Evaluacion 3 - Proyecto Integrador SMTI (Unidad 9: Sockets)
 * Docente   : Ing. Paola Andrea Bedoya Toro
 * Estudiantes: Arturo Ortiz y Sergio David Castillo
 * Archivo   : ServidorSockets.h
 */
#ifndef SERVIDORSOCKETS_H
#define SERVIDORSOCKETS_H

#include "ListaGen.h"
#include "MuestraSensor.h"
#include "Sensor.h"

class ServidorSMTI {
private:
    int server_fd;
    int puerto;

    // Lee EXACTAMENTE 'n' bytes (TCP es un flujo: un recv puede devolver menos).
    // Devuelve false si el cliente cerro limpiamente ANTES de enviar el primer byte.
    bool recibirExacto(int client_fd, void* destino, size_t n);

    // Fabrica: segun muestra.tipo hace "new" de la clase derivada correcta.
    Sensor* crearSensor(const MuestraSensor& m);

public:
    explicit ServidorSMTI(int p);
    ~ServidorSMTI();                       // cierra el socket (RAII)

    ServidorSMTI(const ServidorSMTI&) = delete;
    ServidorSMTI& operator=(const ServidorSMTI&) = delete;

    void iniciar();                        // socket + setsockopt + bind + listen
    // Atiende 'maxClientes' conexiones; cada muestra valida se inserta en la lista.
    void atenderClientes(ListaGen<Sensor*>& lista, int maxClientes);
};

#endif

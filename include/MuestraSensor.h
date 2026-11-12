/*
 * Curso     : Programacion Orientada a Objetos en C++
 * Actividad : Evaluacion 3 - Proyecto Integrador SMTI (Unidad 9: Sockets)
 * Docente   : Ing. Paola Andrea Bedoya Toro
 * Estudiantes: Arturo Ortiz y Sergio David Castillo
 * Archivo   : MuestraSensor.h
 */
#ifndef MUESTRASENSOR_H
#define MUESTRASENSOR_H

// Trama industrial binaria que viaja por el socket TCP.
// El cliente y el servidor deben usar EXACTAMENTE esta misma estructura.
struct MuestraSensor {
    int idSensor;      // identificador del sensor remoto
    double valor;      // lectura (grados, bar, m3/h ...)
    char tipo[12];     // "TEMPERATURA", "PRESION" o "CAUDAL" (terminado en '\0')
};

#endif

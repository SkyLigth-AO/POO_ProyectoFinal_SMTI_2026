/*
 * Curso     : Programacion Orientada a Objetos en C++
 * Actividad : Evaluacion 3 - Proyecto Integrador SMTI (Unidad 9: Sockets)
 * Docente   : Ing. Paola Andrea Bedoya Toro
 * Estudiantes: Arturo Ortiz y Sergio David Castillo
 * Archivo   : SensorPresion.h
 */
#ifndef SENSOR_PRESION_H
#define SENSOR_PRESION_H

#include "Sensor.h"

class SensorPresion : public Sensor {
private:
    double presionMaxima; // bar

public:
    SensorPresion(int _id, const std::string& _ub, double _lect, double _max = 10.0);
    void procesarLectura() override;
};

#endif

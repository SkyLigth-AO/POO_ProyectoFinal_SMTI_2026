/*
 * Curso     : Programacion Orientada a Objetos en C++
 * Actividad : Evaluacion 3 - Proyecto Integrador SMTI (Unidad 9: Sockets)
 * Docente   : Ing. Paola Andrea Bedoya Toro
 * Estudiantes: Arturo Ortiz y Sergio David Castillo
 * Archivo   : SensorCaudal.h
 */
#ifndef SENSOR_CAUDAL_H
#define SENSOR_CAUDAL_H

#include "Sensor.h"

class SensorCaudal : public Sensor {
private:
    double caudalMinimo; // m3/h

public:
    SensorCaudal(int _id, const std::string& _ub, double _lect, double _min = 5.0);
    void procesarLectura() override;
};

#endif

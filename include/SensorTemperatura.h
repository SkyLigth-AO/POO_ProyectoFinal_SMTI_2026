/*
 * Curso     : Programacion Orientada a Objetos en C++
 * Actividad : Evaluacion 3 - Proyecto Integrador SMTI (Unidad 9: Sockets)
 * Docente   : Ing. Paola Andrea Bedoya Toro
 * Estudiantes: Arturo Ortiz y Sergio David Castillo
 * Archivo   : SensorTemperatura.h
 */
#ifndef SENSOR_TEMPERATURA_H
#define SENSOR_TEMPERATURA_H

#include "Sensor.h"

class SensorTemperatura : public Sensor {
private:
    double umbralMaximo;

public:
    SensorTemperatura(int _id, const std::string& _ub, double _lect, double _umbral = 80.0);

    // 'override' -> el compilador verifica que realmente sobrescribe un virtual de la base
    void procesarLectura() override;
};

#endif

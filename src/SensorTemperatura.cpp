/*
 * Curso     : Programacion Orientada a Objetos en C++
 * Actividad : Evaluacion 3 - Proyecto Integrador SMTI (Unidad 9: Sockets)
 * Docente   : Ing. Paola Andrea Bedoya Toro
 * Estudiantes: Arturo Ortiz y Sergio David Castillo
 * Archivo   : SensorTemperatura.cpp
 */
#include "../include/SensorTemperatura.h"

SensorTemperatura::SensorTemperatura(int _id, const std::string& _ub, double _lect, double _umbral)
    : Sensor(_id, _ub, _lect), umbralMaximo(_umbral) {}

void SensorTemperatura::procesarLectura() {
    std::cout << "[TEMP POLIMORFICO] " << *this;
    if (lectura > umbralMaximo) {
        std::cout << " --> ALERTA: SOBRETEMPERATURA CRITICA!";
    }
    std::cout << std::endl;
}

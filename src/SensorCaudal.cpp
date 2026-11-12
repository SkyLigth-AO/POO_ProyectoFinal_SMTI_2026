/*
 * Curso     : Programacion Orientada a Objetos en C++
 * Actividad : Evaluacion 3 - Proyecto Integrador SMTI (Unidad 9: Sockets)
 * Docente   : Ing. Paola Andrea Bedoya Toro
 * Estudiantes: Arturo Ortiz y Sergio David Castillo
 * Archivo   : SensorCaudal.cpp
 */
#include "../include/SensorCaudal.h"

SensorCaudal::SensorCaudal(int _id, const std::string& _ub, double _lect, double _min)
    : Sensor(_id, _ub, _lect), caudalMinimo(_min) {}

void SensorCaudal::procesarLectura() {
    std::cout << "[CAUDAL POLIMORFICO] " << *this << " m3/h";
    if (lectura < caudalMinimo) {
        std::cout << " --> ALERTA: CAUDAL BAJO!";
    }
    std::cout << std::endl;
}

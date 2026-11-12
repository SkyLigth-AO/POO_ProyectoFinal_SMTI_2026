/*
 * Curso     : Programacion Orientada a Objetos en C++
 * Actividad : Evaluacion 3 - Proyecto Integrador SMTI (Unidad 9: Sockets)
 * Docente   : Ing. Paola Andrea Bedoya Toro
 * Estudiantes: Arturo Ortiz y Sergio David Castillo
 * Archivo   : SensorPresion.cpp
 */
#include "../include/SensorPresion.h"

SensorPresion::SensorPresion(int _id, const std::string& _ub, double _lect, double _max)
    : Sensor(_id, _ub, _lect), presionMaxima(_max) {}

void SensorPresion::procesarLectura() {
    std::cout << "[PRESION POLIMORFICO] " << *this << " bar";
    if (lectura > presionMaxima) {
        std::cout << " --> ALERTA: SOBREPRESION!";
    }
    std::cout << std::endl;
}

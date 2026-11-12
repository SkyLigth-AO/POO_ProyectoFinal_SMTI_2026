/*
 * Curso     : Programacion Orientada a Objetos en C++
 * Actividad : Evaluacion 3 - Proyecto Integrador SMTI (Unidad 9: Sockets)
 * Docente   : Ing. Paola Andrea Bedoya Toro
 * Estudiantes: Arturo Ortiz y Sergio David Castillo
 * Archivo   : Sensor.cpp
 */
#include "../include/Sensor.h"

Sensor::Sensor(int _id, const std::string& _ub, double _lect)
    : id(_id), ubicacion(_ub), lectura(_lect) {}

Sensor::~Sensor() {
    std::cout << "[DESTRUCTOR] Sensor ID " << id << " liberado del Heap." << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Sensor& s) {
    os << "Sensor ID: " << s.id << " | Ubicacion: " << s.ubicacion
       << " | Valor: " << s.lectura;
    return os;
}

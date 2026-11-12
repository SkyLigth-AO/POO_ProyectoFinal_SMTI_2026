/*
 * Curso     : Programacion Orientada a Objetos en C++
 * Actividad : Evaluacion 3 - Proyecto Integrador SMTI (Unidad 9: Sockets)
 * Docente   : Ing. Paola Andrea Bedoya Toro
 * Estudiantes: Arturo Ortiz y Sergio David Castillo
 * Archivo   : Sensor.h
 */
#ifndef SENSOR_H
#define SENSOR_H

#include <iostream>
#include <string>

// Clase base ABSTRACTA: tiene un metodo virtual puro -> no se puede instanciar.
class Sensor {
protected:
    int id;
    std::string ubicacion;
    double lectura;

public:
    Sensor(int _id, const std::string& _ub, double _lect);

    // Destructor VIRTUAL: sin el, "delete sensorPtr" (puntero Sensor*) solo
    // llamaria ~Sensor() y NO el de la clase derivada -> fuga / comportamiento indefinido.
    virtual ~Sensor();

    int getId() const { return id; }
    double getLectura() const { return lectura; }

    // Metodo virtual puro: cada derivada DEBE implementarlo.
    virtual void procesarLectura() = 0;

    // Sobrecarga de operador amiga (acceso a miembros protegidos)
    friend std::ostream& operator<<(std::ostream& os, const Sensor& s);
};

#endif

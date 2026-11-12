/*
 * Curso     : Programacion Orientada a Objetos en C++
 * Actividad : Evaluacion 3 - Proyecto Integrador SMTI (Unidad 9: Sockets)
 * Docente   : Ing. Paola Andrea Bedoya Toro
 * Estudiantes: Arturo Ortiz y Sergio David Castillo
 * Archivo   : ExcepcionesSMTI.h
 */
#ifndef EXCEPCIONESSMTI_H
#define EXCEPCIONESSMTI_H

#include <stdexcept>
#include <string>

// Todas heredan de std::runtime_error, asi que un
// catch (const std::exception& e) en main() las atrapa a todas.

// Fallo de socket / bind / listen / accept / recv (infraestructura de red)
class ErrorRedSMTI : public std::runtime_error {
public:
    explicit ErrorRedSMTI(const std::string& msg)
        : std::runtime_error("[RED] " + msg) {}
};

// Trama recibida con formato invalido (tipo desconocido, id <= 0, etc.)
class ErrorTramaSMTI : public std::runtime_error {
public:
    explicit ErrorTramaSMTI(const std::string& msg)
        : std::runtime_error("[TRAMA] " + msg) {}
};

#endif

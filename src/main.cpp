/*
 * Curso     : Programacion Orientada a Objetos en C++
 * Actividad : Evaluacion 3 - Proyecto Integrador SMTI (Unidad 9: Sockets)
 * Docente   : Ing. Paola Andrea Bedoya Toro
 * Estudiantes: Arturo Ortiz y Sergio David Castillo
 * Archivo   : main.cpp
 */
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include "../include/Sensor.h"
#include "../include/ListaGen.h"
#include "../include/ServidorSockets.h"

// Uso: ./smti [numClientes]   (por defecto atiende 1 cliente y termina)
int main(int argc, char* argv[]) {
    std::cout << "==================================================" << std::endl;
    std::cout << " SMTI: SERVIDOR DE TELEMETRIA DISTRIBUIDA (UNIDAD 9)" << std::endl;
    std::cout << " Estudiantes: Arturo Ortiz y Sergio David Castillo" << std::endl;
    std::cout << "==================================================" << std::endl;

    int maxClientes = (argc > 1) ? std::atoi(argv[1]) : 1;
    if (maxClientes < 1) maxClientes = 1;

    // Se declara ANTES del try: sobrevive al catch y se destruye al salir de main()
    ListaGen<Sensor*> listaPlanta;

    try {
        ServidorSMTI servidor(8080);
        servidor.iniciar();                              // socket, bind, listen
        servidor.atenderClientes(listaPlanta, maxClientes); // accept + recv

        std::cout << "\n--- PROCESAMIENTO POLIMORFICO DE TELEMETRIA ("
                  << listaPlanta.getTamanio() << " muestras) ---" << std::endl;
        listaPlanta.procesarTodo();                      // dynamic binding via vtable

        std::cout << "\n--- BUSQUEDA POR ID (102) ---" << std::endl;
        Sensor* s = listaPlanta.buscarPorId(102);
        if (s) std::cout << *s << std::endl;
        else   std::cout << "Sensor 102 no encontrado." << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "[EXCEPCION GRAVE SMTI] " << e.what() << std::endl;
        return 1;   // la lista igual se destruye limpiamente al salir
    }

    std::cout << "\n--- LIBERANDO MEMORIA (~ListaGen) ---" << std::endl;
    return 0;
}

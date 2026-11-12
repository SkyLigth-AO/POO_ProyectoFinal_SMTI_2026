/*
 * Curso     : Programacion Orientada a Objetos en C++
 * Actividad : Evaluacion 3 - Proyecto Integrador SMTI (Unidad 9: Sockets)
 * Docente   : Ing. Paola Andrea Bedoya Toro
 * Estudiantes: Arturo Ortiz y Sergio David Castillo
 * Archivo   : ServidorSockets.cpp
 */
#include "../include/ServidorSockets.h"
#include "../include/ExcepcionesSMTI.h"
#include "../include/SensorTemperatura.h"
#include "../include/SensorPresion.h"
#include "../include/SensorCaudal.h"

#include <cerrno>
#include <cmath>
#include <cstring>
#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

ServidorSMTI::ServidorSMTI(int p) : server_fd(-1), puerto(p) {}

ServidorSMTI::~ServidorSMTI() {
    if (server_fd >= 0) close(server_fd);
}

void ServidorSMTI::iniciar() {
    // 1. socket(): crea el descriptor TCP IPv4
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        throw ErrorRedSMTI("No se pudo crear el socket: " + std::string(std::strerror(errno)));
    }

    // Permite reusar el puerto sin esperar el TIME_WAIT
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // 2. Direccion local
    sockaddr_in addr;
    std::memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;   // todas las interfaces
    addr.sin_port = htons(puerto);       // host -> network byte order

    // 3. bind(): falla si el puerto esta ocupado
    if (bind(server_fd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0) {
        throw ErrorRedSMTI("bind fallido en puerto " + std::to_string(puerto) +
                           " (" + std::strerror(errno) + ")");
    }

    // 4. listen(): modo pasivo, cola de 5 conexiones pendientes
    if (listen(server_fd, 5) < 0) {
        throw ErrorRedSMTI("listen fallido: " + std::string(std::strerror(errno)));
    }

    std::cout << "[SERVIDOR SMTI] Escuchando telemetria en puerto " << puerto << "..." << std::endl;
}

bool ServidorSMTI::recibirExacto(int client_fd, void* destino, size_t n) {
    char* p = static_cast<char*>(destino);
    size_t total = 0;
    while (total < n) {
        ssize_t r = recv(client_fd, p + total, n - total, 0);
        if (r < 0) {
            if (errno == EINTR) continue;
            throw ErrorRedSMTI("recv fallido: " + std::string(std::strerror(errno)));
        }
        if (r == 0) {                       // el cliente cerro la conexion
            if (total == 0) return false;   // cierre limpio entre tramas
            throw ErrorTramaSMTI("Trama incompleta: llegaron " + std::to_string(total) +
                                 " de " + std::to_string(n) + " bytes.");
        }
        total += static_cast<size_t>(r);
    }
    return true;
}

Sensor* ServidorSMTI::crearSensor(const MuestraSensor& m) {
    if (m.idSensor <= 0)
        throw ErrorTramaSMTI("idSensor invalido: " + std::to_string(m.idSensor));
    if (!std::isfinite(m.valor))
        throw ErrorTramaSMTI("valor no numerico en sensor " + std::to_string(m.idSensor));

    // Defensa: garantizar que 'tipo' termine en '\0' aunque el cliente no lo haya enviado
    char tipoSeguro[sizeof(m.tipo) + 1];
    std::memcpy(tipoSeguro, m.tipo, sizeof(m.tipo));
    tipoSeguro[sizeof(m.tipo)] = '\0';
    std::string tipo(tipoSeguro);

    std::string ubicacion = "Nodo-remoto-" + std::to_string(m.idSensor);

    if (tipo == "TEMPERATURA") return new SensorTemperatura(m.idSensor, ubicacion, m.valor);
    if (tipo == "PRESION")     return new SensorPresion(m.idSensor, ubicacion, m.valor);
    if (tipo == "CAUDAL")      return new SensorCaudal(m.idSensor, ubicacion, m.valor);

    throw ErrorTramaSMTI("Tipo de sensor desconocido: '" + tipo + "'");
}

void ServidorSMTI::atenderClientes(ListaGen<Sensor*>& lista, int maxClientes) {
    for (int c = 1; c <= maxClientes; ++c) {
        sockaddr_in cliente;
        socklen_t len = sizeof(cliente);

        // 5. accept(): BLOQUEA hasta que llega un cliente; devuelve un socket NUEVO
        int client_fd = accept(server_fd, reinterpret_cast<sockaddr*>(&cliente), &len);
        if (client_fd < 0) {
            throw ErrorRedSMTI("accept fallido: " + std::string(std::strerror(errno)));
        }
        std::cout << "[SERVIDOR SMTI] Cliente " << c << "/" << maxClientes << " conectado." << std::endl;

        try {
            MuestraSensor m;
            // 6. recv(): se lee trama por trama hasta que el cliente cierra
            while (recibirExacto(client_fd, &m, sizeof(m))) {
                try {
                    Sensor* s = crearSensor(m);   // new en el Heap
                    lista.insertar(s);            // la lista pasa a ser duena del puntero
                    std::cout << "[SERVIDOR SMTI] Muestra aceptada: " << *s << std::endl;
                } catch (const ErrorTramaSMTI& e) {
                    // Trama mala: se descarta y se sigue atendiendo (no tumba el servidor)
                    std::cerr << "[SERVIDOR SMTI] Trama descartada -> " << e.what() << std::endl;
                }
            }
        } catch (...) {
            close(client_fd);   // no dejar el descriptor abierto si algo falla
            throw;              // relanzar al main()
        }
        close(client_fd);
        std::cout << "[SERVIDOR SMTI] Cliente " << c << " desconectado." << std::endl;
    }
}

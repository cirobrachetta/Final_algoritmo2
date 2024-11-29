#pragma once
#include "Mensaje.hpp"
#include <iostream>
#include <string>

class MockMensaje : public Mensaje {
public:
    bool mensajeEnviado = false; // Indicador para verificar si se llamó a enviarMensaje

    void enviarMensaje(const Cliente& cliente, const std::string& mensaje) override {
        mensajeEnviado = true;
        std::cout << "MockMensaje: Simulación de mensaje enviado al cliente "
                  << cliente.getNombre() << " (ID: " << cliente.getId() << "): " << mensaje << "\n";
    }
};
#pragma once
#include "Cliente.hpp"

class Mensaje {
public:
    virtual void enviarMensaje(const Cliente& cliente, const string& mensaje) = 0;
    virtual ~Mensaje() = default;
};

class MensajeWhatsApp : public Mensaje {
public:
    void enviarMensaje(const Cliente& cliente, const string& mensaje) override;
};
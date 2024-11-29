#pragma once
#include <memory>
#include <vector>
#include "Cliente.hpp"
#include "Cubiculo.hpp"
#include "Mensaje.hpp"

class Alquiler {
private:
    shared_ptr<Mensaje> metodoNotificacion;

public:
    int id;
    shared_ptr<Cliente> cliente;
    vector<shared_ptr<Cubiculo>> cubiculos;
    string fechaInicio;
    string fechaFin;

    Alquiler(int id, shared_ptr<Cliente> cliente, shared_ptr<Mensaje> notificador);

    void agregarCubiculo(const shared_ptr<Cubiculo>& cubiculo);
    void notificar();
};
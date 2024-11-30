#pragma once
#include <memory>
#include <vector>
#include "Cliente.hpp"
#include "Cubiculo.hpp"
#include "Alquiler.hpp"

class GestorAlquileres {
private:
    vector<shared_ptr<Cliente>> clientes;
    vector<shared_ptr<Cubiculo>> cubiculos;
    vector<shared_ptr<Alquiler>> alquileres;

public:
    // Métodos para gestionar clientes
    void altaCliente(int id, const string& nombre, const string& contacto);
    void bajaCliente(int id);
    void modificarCliente(int id, const string& nuevoNombre, const string& nuevoContacto);
    vector<shared_ptr<Cliente>> listarClientes() const;

    // Métodos para gestionar cubículos
    void altaCubiculo(int id, const string& ubicacion);
    void bajaCubiculo(int id);
    void modificarCubiculo(int id, const string& nuevaUbicacion, const string& nuevoEstado);
    vector<shared_ptr<Cubiculo>> listarCubiculos() const;

    // Métodos para gestionar alquileres
    void altaAlquiler(int id, int clienteId, const vector<int>& idsCubiculos, const string& fechaInicio, const string& fechaFin);
    void bajaAlquiler(int id);
    vector<shared_ptr<Alquiler>> listarAlquileres() const;
};

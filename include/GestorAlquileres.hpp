#pragma once
#include <vector>
#include <memory>
#include "Cliente.hpp"
#include "Cubiculo.hpp"
#include "Alquiler.hpp"

class GestorAlquileres {
private:
    vector<shared_ptr<Cliente>> clientes;
    vector<shared_ptr<Cubiculo>> cubiculos;
    vector<shared_ptr<Alquiler>> alquileres;

public:
    // Constructor
    GestorAlquileres();

    // Métodos para alta
    void altaCliente(int id, const string& nombre, const string& contacto);
    void altaCubiculo(int id, const string& ubicacion);
    void altaAlquiler(int idAlquiler, int idCliente, const vector<int>& idsCubiculos, const string& fechaInicio, const string& fechaFin);

    // Métodos para listar
    vector<shared_ptr<Cliente>> listarClientes() const;
    vector<shared_ptr<Cubiculo>> listarCubiculos() const;
    vector<shared_ptr<Alquiler>> listarAlquileres() const;
};
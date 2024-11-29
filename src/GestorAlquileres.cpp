#include "GestorAlquileres.hpp"
#include <stdexcept>
#include <algorithm>

// Constructor
GestorAlquileres::GestorAlquileres() {}

// Función para agregar un cliente
void GestorAlquileres::altaCliente(int id, const string& nombre, const string& contacto) {
    if (any_of(clientes.begin(), clientes.end(), [id](const auto& cliente) { return cliente->getId() == id; })) {
        throw runtime_error("Ya existe un cliente con el ID proporcionado.");
    }
    clientes.push_back(make_shared<Cliente>(id, nombre, contacto));
}

// Función para agregar un cubículo
void GestorAlquileres::altaCubiculo(int id, const string& ubicacion) {
    if (any_of(cubiculos.begin(), cubiculos.end(), [id](const auto& cubiculo) { return cubiculo->getId() == id; })) {
        throw runtime_error("Ya existe un cubiculo con el ID proporcionado.");
    }
    cubiculos.push_back(make_shared<Cubiculo>(id, ubicacion));
}

// Función para registrar un alquiler
void GestorAlquileres::altaAlquiler(int idAlquiler, int idCliente, const vector<int>& idsCubiculos,
                                    const string& fechaInicio, const string& fechaFin) {
    if (any_of(alquileres.begin(), alquileres.end(), [idAlquiler](const auto& alquiler) { return alquiler->id == idAlquiler; })) {
        throw runtime_error("Ya existe un alquiler con el ID proporcionado.");
    }

    auto clienteIt = find_if(clientes.begin(), clientes.end(), [idCliente](const auto& cliente) { return cliente->getId() == idCliente; });
    if (clienteIt == clientes.end()) {
        throw runtime_error("Cliente no encontrado.");
    }

    vector<shared_ptr<Cubiculo>> cubiculosSeleccionados;
    for (int idCubiculo : idsCubiculos) {
        auto cubiculoIt = find_if(cubiculos.begin(), cubiculos.end(),
                                       [idCubiculo](const auto& cubiculo) { return cubiculo->getId() == idCubiculo; });
        if (cubiculoIt == cubiculos.end()) {
            throw runtime_error("Cubículo no encontrado: ID " + to_string(idCubiculo));
        }
        cubiculosSeleccionados.push_back(*cubiculoIt);
    }

    alquileres.push_back(make_shared<Alquiler>(idAlquiler, *clienteIt, cubiculosSeleccionados, fechaInicio, fechaFin));
}

// Función para listar clientes
vector<shared_ptr<Cliente>> GestorAlquileres::listarClientes() const {
    return clientes;
}

// Función para listar cubículos
vector<shared_ptr<Cubiculo>> GestorAlquileres::listarCubiculos() const {
    return cubiculos;
}

// Función para listar alquileres
vector<shared_ptr<Alquiler>> GestorAlquileres::listarAlquileres() const {
    return alquileres;
}

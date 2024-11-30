#include "GestorAlquileres.hpp"
#include <stdexcept>
#include <algorithm>

// Métodos de gestion de clientes
void GestorAlquileres::altaCliente(int id, const string& nombre, const string& contacto) {
    auto cliente = make_shared<Cliente>(id, nombre, contacto);
    clientes.push_back(cliente);
}

void GestorAlquileres::bajaCliente(int id) {
    auto it = remove_if(clientes.begin(), clientes.end(), [id](const auto& cliente) {
        return cliente->getId() == id;
    });

    if (it != clientes.end()) {
        clientes.erase(it, clientes.end());
    } else {
        throw runtime_error("Cliente no encontrado");
    }
}

void GestorAlquileres::modificarCliente(int id, const string& nuevoNombre, const string& nuevoContacto) {
    for (auto& cliente : clientes) {
        if (cliente->getId() == id) {
            cliente->setNombre(nuevoNombre);
            cliente->setContacto(nuevoContacto);
            return;
        }
    }
    throw runtime_error("Cliente no encontrado");
}

vector<shared_ptr<Cliente>> GestorAlquileres::listarClientes() const {
    return clientes;
}

// Métodos de gestion de cubiculos
void GestorAlquileres::altaCubiculo(int id, const string& ubicacion) {
    auto cubiculo = make_shared<Cubiculo>(id, ubicacion);
    cubiculos.push_back(cubiculo);
}

void GestorAlquileres::bajaCubiculo(int id) {
    auto it = remove_if(cubiculos.begin(), cubiculos.end(), [id](const auto& cubiculo) {
        return cubiculo->getId() == id;
    });

    if (it != cubiculos.end()) {
        cubiculos.erase(it, cubiculos.end());
    } else {
        throw runtime_error("Cubiculo no encontrado");
    }
}

void GestorAlquileres::modificarCubiculo(int id, const string& nuevaUbicacion, const string& nuevoEstado) {
    for (auto& cubiculo : cubiculos) {
        if (cubiculo->getId() == id) {
            cubiculo->setUbicacion(nuevaUbicacion);
            cubiculo->setEstado(nuevoEstado);
            return;
        }
    }
    throw runtime_error("Cubiculo no encontrado");
}

vector<shared_ptr<Cubiculo>> GestorAlquileres::listarCubiculos() const {
    return cubiculos;
}

// Métodos de gestion de alquileres
void GestorAlquileres::altaAlquiler(int id, int clienteId, const vector<int>& idsCubiculos, const string& fechaInicio, const string& fechaFin) {
    // Validar ID del cliente
    auto clienteIt = find_if(clientes.begin(), clientes.end(), [clienteId](const auto& cliente) {
        return cliente->getId() == clienteId;
    });

    if (clienteIt == clientes.end()) {
        throw runtime_error("Cliente no encontrado");
    }

    // Validar IDs de cubiculos seleccionados
    vector<shared_ptr<Cubiculo>> alquilerCubiculos;
    for (int cubiculoId : idsCubiculos) {
        auto cubiculoIt = find_if(cubiculos.begin(), cubiculos.end(), [cubiculoId](const auto& cubiculo) {
            return cubiculo->getId() == cubiculoId;
        });

        if (cubiculoIt == cubiculos.end()) {
            throw runtime_error("Cubiculo con ID " + to_string(cubiculoId) + " no encontrado");
        }

        if ((*cubiculoIt)->getEstado() != "Disponible") {
            throw runtime_error("Cubiculo con ID " + to_string(cubiculoId) + " no está disponible");
        }

        alquilerCubiculos.push_back(*cubiculoIt);
    }

    // Crear y registrar el alquiler
    auto alquiler = make_shared<Alquiler>(id, *clienteIt, nullptr);
    alquiler->cubiculos = alquilerCubiculos;
    alquiler->fechaInicio = fechaInicio;
    alquiler->fechaFin = fechaFin;
    alquileres.push_back(alquiler);

    // Cambiar el estado de los cubiculos a "Alquilado"
    for (auto& cubiculo : alquilerCubiculos) {
        cubiculo->setEstado("Alquilado");
    }

    cout << "Alquiler registrado correctamente.\n";
}

void GestorAlquileres::bajaAlquiler(int id) {
    auto it = remove_if(alquileres.begin(), alquileres.end(), [id](const auto& alquiler) {
        return alquiler->id == id;
    });

    if (it != alquileres.end()) {
        alquileres.erase(it, alquileres.end());
    } else {
        throw runtime_error("Alquiler no encontrado");
    }
}

vector<shared_ptr<Alquiler>> GestorAlquileres::listarAlquileres() const {
    return alquileres;
}

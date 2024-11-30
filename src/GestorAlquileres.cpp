#include "GestorAlquileres.hpp"
#include <stdexcept>
#include <algorithm>

// Métodos de gestión de clientes
void GestorAlquileres::altaCliente(int id, const std::string& nombre, const std::string& contacto) {
    auto cliente = std::make_shared<Cliente>(id, nombre, contacto);
    clientes.push_back(cliente);
}

void GestorAlquileres::bajaCliente(int id) {
    auto it = std::remove_if(clientes.begin(), clientes.end(), [id](const auto& cliente) {
        return cliente->getId() == id;
    });

    if (it != clientes.end()) {
        clientes.erase(it, clientes.end());
    } else {
        throw std::runtime_error("Cliente no encontrado");
    }
}

void GestorAlquileres::modificarCliente(int id, const std::string& nuevoNombre, const std::string& nuevoContacto) {
    for (auto& cliente : clientes) {
        if (cliente->getId() == id) {
            cliente->setNombre(nuevoNombre);
            cliente->setContacto(nuevoContacto);
            return;
        }
    }
    throw std::runtime_error("Cliente no encontrado");
}

std::vector<std::shared_ptr<Cliente>> GestorAlquileres::listarClientes() const {
    return clientes;
}

// Métodos de gestión de cubículos
void GestorAlquileres::altaCubiculo(int id, const std::string& ubicacion) {
    auto cubiculo = std::make_shared<Cubiculo>(id, ubicacion);
    cubiculos.push_back(cubiculo);
}

void GestorAlquileres::bajaCubiculo(int id) {
    auto it = std::remove_if(cubiculos.begin(), cubiculos.end(), [id](const auto& cubiculo) {
        return cubiculo->getId() == id;
    });

    if (it != cubiculos.end()) {
        cubiculos.erase(it, cubiculos.end());
    } else {
        throw std::runtime_error("Cubículo no encontrado");
    }
}

void GestorAlquileres::modificarCubiculo(int id, const std::string& nuevaUbicacion, const std::string& nuevoEstado) {
    for (auto& cubiculo : cubiculos) {
        if (cubiculo->getId() == id) {
            cubiculo->setUbicacion(nuevaUbicacion);
            cubiculo->setEstado(nuevoEstado);
            return;
        }
    }
    throw std::runtime_error("Cubículo no encontrado");
}

std::vector<std::shared_ptr<Cubiculo>> GestorAlquileres::listarCubiculos() const {
    return cubiculos;
}

// Métodos de gestión de alquileres
void GestorAlquileres::altaAlquiler(int id, int clienteId, const std::vector<int>& idsCubiculos, const std::string& fechaInicio, const std::string& fechaFin) {
    auto clienteIt = std::find_if(clientes.begin(), clientes.end(), [clienteId](const auto& cliente) {
        return cliente->getId() == clienteId;
    });

    if (clienteIt == clientes.end()) {
        throw std::runtime_error("Cliente no encontrado");
    }

    std::vector<std::shared_ptr<Cubiculo>> alquilerCubiculos;
    for (int cubiculoId : idsCubiculos) {
        auto cubiculoIt = std::find_if(cubiculos.begin(), cubiculos.end(), [cubiculoId](const auto& cubiculo) {
            return cubiculo->getId() == cubiculoId;
        });

        if (cubiculoIt == cubiculos.end()) {
            throw std::runtime_error("Cubículo con ID " + std::to_string(cubiculoId) + " no encontrado");
        }

        alquilerCubiculos.push_back(*cubiculoIt);
    }

    auto alquiler = std::make_shared<Alquiler>(id, *clienteIt, nullptr);
    alquiler->cubiculos = alquilerCubiculos;
    alquiler->fechaInicio = fechaInicio;
    alquiler->fechaFin = fechaFin;
    alquileres.push_back(alquiler);
}

void GestorAlquileres::bajaAlquiler(int id) {
    auto it = std::remove_if(alquileres.begin(), alquileres.end(), [id](const auto& alquiler) {
        return alquiler->id == id;
    });

    if (it != alquileres.end()) {
        alquileres.erase(it, alquileres.end());
    } else {
        throw std::runtime_error("Alquiler no encontrado");
    }
}

std::vector<std::shared_ptr<Alquiler>> GestorAlquileres::listarAlquileres() const {
    return alquileres;
}

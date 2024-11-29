#include "Cubiculo.hpp"

Cubiculo::Cubiculo(int id, const string& ubicacion, const string& estado)
    : id(id), ubicacion(ubicacion), estado(estado) {}

// Getters
int Cubiculo::getId() const {
    return id;
}

string Cubiculo::getUbicacion() const {
    return ubicacion;
}

string Cubiculo::getEstado() const {
    return estado;
}

// Setters
void Cubiculo::setUbicacion(const string& nuevaUbicacion) {
    ubicacion = nuevaUbicacion;
}

void Cubiculo::setEstado(const string& nuevoEstado) {
    estado = nuevoEstado;
}

#include "Cliente.hpp"

Cliente::Cliente(int id, const string& nombre, const string& contacto)
    : id(id), nombre(nombre), contacto(contacto) {}

// Getters
int Cliente::getId() const {
    return id;
}

string Cliente::getNombre() const {
    return nombre;
}

string Cliente::getContacto() const {
    return contacto;
}

// Setters
void Cliente::setNombre(const string& nuevoNombre) {
    nombre = nuevoNombre;
}

void Cliente::setContacto(const string& nuevoContacto) {
    contacto = nuevoContacto;
}

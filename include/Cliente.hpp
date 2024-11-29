#pragma once
#include <iostream>
using namespace std;

class Cliente {
private:
    int id;
    string nombre;
    string contacto;

public:
    Cliente(int id, const string& nombre, const string& contacto);

    // Getters
    int getId() const;
    string getNombre() const;
    string getContacto() const;

    // Setters
    void setNombre(const string& nuevoNombre);
    void setContacto(const string& nuevoContacto);
};

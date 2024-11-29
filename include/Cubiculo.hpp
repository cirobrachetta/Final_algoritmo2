#pragma once
#include <iostream>
using namespace std;

class Cubiculo {
private:
    int id;
    string ubicacion;
    string estado; // "Disponible", "Reservado", "Alquilado"

public:
    Cubiculo(int id, const string& ubicacion, const string& estado = "Disponible");

    // Getters
    int getId() const;
    string getUbicacion() const;
    string getEstado() const;

    // Setters
    void setUbicacion(const string& nuevaUbicacion);
    void setEstado(const string& nuevoEstado);
};

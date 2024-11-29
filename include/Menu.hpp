#pragma once
#include <memory>
#include <vector>
#include "Cliente.hpp"
#include "Cubiculo.hpp"
#include "Alquiler.hpp"
#include "Mensaje.hpp"

using namespace std;

class Menu {
private:
    vector<shared_ptr<Cliente>> clientes;
    vector<shared_ptr<Cubiculo>> cubiculos;
    vector<shared_ptr<Alquiler>> alquileres;

    void agregarCliente();
    void agregarCubiculo();
    void agregarAlquiler();
    void mostrarAlquileres() const;

public:
    void mostrarMenu();

    // Métodos para pruebas
    void altaCliente(int id, const string& nombre, const string& contacto);
    void bajaCliente(int id);
    void modificarCliente(int id, const string& nuevoNombre, const string& nuevoContacto);
    shared_ptr<Cliente> buscarCliente(int id);
    vector<shared_ptr<Alquiler>> listarAlquileres() const;


    void altaAlquiler(int idAlquiler, int idCliente, const vector<int>& idsCubiculos, const string& fechaInicio, const string& fechaFin);
    void altaCubiculo(int id, const string& ubicacion);
    void bajaCubiculo(int id);
    void modificarCubiculo(int id, const string& nuevaUbicacion);
    shared_ptr<Cubiculo> buscarCubiculo(int id);

    shared_ptr<Alquiler> buscarAlquiler(int id);
    vector<shared_ptr<Alquiler>> listarAlquileresVector();
};
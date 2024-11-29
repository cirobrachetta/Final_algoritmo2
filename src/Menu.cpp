#include "Menu.hpp"
#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>
#include "Cliente.hpp"
#include "Cubiculo.hpp"
#include "Mensaje.hpp"
#include "Alquiler.hpp"

using namespace std;

// Almacenamiento en memoria
vector<shared_ptr<Cliente>> clientes;
vector<shared_ptr<Cubiculo>> cubiculos;
vector<shared_ptr<Alquiler>> alquileres;

// Métodos auxiliares para el menú

void Menu::agregarCliente() {
    int id;
    string nombre, contacto;

    cout << "Ingrese ID del cliente: ";
    cin >> id;
    cin.ignore(); // Limpiar buffer

    cout << "Ingrese nombre del cliente: ";
    getline(cin, nombre);

    cout << "Ingrese contacto del cliente: ";
    getline(cin, contacto);

    altaCliente(id, nombre, contacto);

    cout << "Cliente agregado correctamente.\n";
}

void Menu::agregarCubiculo() {
    int id;
    string ubicacion;

    cout << "Ingrese ID del cubiculo: ";
    cin >> id;
    cin.ignore(); // Limpiar buffer

    cout << "Ingrese ubicacion del cubiculo: ";
    getline(cin, ubicacion);

    altaCubiculo(id, ubicacion);

    cout << "Cubiculo agregado correctamente.\n";
}

void Menu::agregarAlquiler() {
    if (clientes.empty() || cubiculos.empty()) {
        cout << "Debe haber al menos un cliente y un cubiculo disponible.\n";
        return;
    }

    int id, clienteId, cubiculoId;
    string fechaInicio, fechaFin;

    cout << "Ingrese ID del alquiler: ";
    cin >> id;

    cout << "Seleccione ID del cliente: \n";
    cout << "\nClientes Reguistrados \n";
    cout << "-------------------------- \n";
    for (const auto& cliente : clientes) {
        cout << cliente->getId() << ". " << cliente->getNombre() << "\n";
    }
    cin >> clienteId;

    auto cliente = buscarCliente(clienteId);
    if (!cliente) {
        cout << "Cliente no encontrado.\n";
        return;
    }

    cout << "Seleccione ID del cubiculo disponible: \n";
    cout << "\nCubiculos Reguistrados \n";
    cout << "-------------------------- \n";
    for (const auto& cubiculo : cubiculos) {
        if (cubiculo->getEstado() == "Disponible") {
            cout << cubiculo->getId() << ". " << cubiculo->getUbicacion() << "\n";
        }
    }
    cin >> cubiculoId;

    auto cubiculo = buscarCubiculo(cubiculoId);
    if (!cubiculo || cubiculo->getEstado() != "Disponible") {
        cout << "Cubiculo no encontrado o no disponible.\n";
        return;
    }

    cin.ignore(); // Limpiar buffer
    cout << "Ingrese fecha de inicio (YYYY-MM-DD): ";
    getline(cin, fechaInicio);

    cout << "Ingrese fecha de fin (YYYY-MM-DD): ";
    getline(cin, fechaFin);

    auto notificador = make_shared<MensajeWhatsApp>();
    auto alquiler = make_shared<Alquiler>(id, cliente, notificador);

    alquiler->agregarCubiculo(cubiculo);
    alquiler->fechaInicio = fechaInicio;
    alquiler->fechaFin = fechaFin;
    
    alquileres.push_back(alquiler);

    cout << "Alquiler registrado correctamente.\n";
}

void Menu::altaAlquiler(int idAlquiler, int idCliente, const vector<int>& idsCubiculos,
                        const string& fechaInicio, const string& fechaFin) {
    auto cliente = buscarCliente(idCliente);
    if (!cliente) throw runtime_error("Cliente no encontrado");

    vector<shared_ptr<Cubiculo>> cubiculosAlquiler;
    for (int idCubiculo : idsCubiculos) {
        auto cubiculo = buscarCubiculo(idCubiculo);
        if (!cubiculo) throw runtime_error("Cubículo no encontrado");
        cubiculosAlquiler.push_back(cubiculo);
    }

    auto alquiler = make_shared<Alquiler>(idAlquiler, cliente, nullptr); // Asume un notificador vacío por ahora
    alquiler->cubiculos = cubiculosAlquiler;
    alquiler->fechaInicio = fechaInicio;
    alquiler->fechaFin = fechaFin;

    alquileres.push_back(alquiler);
}

vector<shared_ptr<Alquiler>> Menu::listarAlquileres() const {
    return alquileres; // Devuelve el vector de alquileres
}


void Menu::mostrarAlquileres() const {
    if (alquileres.empty()) {
        cout << "No hay alquileres registrados.\n";
        return;
    }

    cout << "\nAlquileres Registrados:\n";
    cout << "---------------------------\n";

    for (const auto& alquiler : alquileres) {
        cout << "Alquiler ID: " << alquiler->id << "\n";
        cout << "Cliente: " << alquiler->cliente->getNombre() << "\n";
        cout << "Fecha Inicio: " << alquiler->fechaInicio << "\n";
        cout << "Fecha Fin: " << alquiler->fechaFin << "\n";
        cout << "Cubiculos:\n";

        for (const auto& cubiculo : alquiler->cubiculos) {
            cout << "  - " << cubiculo->getId() << ": " << cubiculo->getUbicacion() << "\n";
        }
        cout << "-----------------------------\n";
    }
}

// Métodos auxiliares para pruebas

void Menu::altaCliente(int id, const string& nombre, const string& contacto) {
    auto cliente = make_shared<Cliente>(id, nombre, contacto);
    clientes.push_back(cliente);
}

void Menu::bajaCliente(int id) {
    clientes.erase(remove_if(clientes.begin(), clientes.end(),
                             [id](const shared_ptr<Cliente>& c) { return c->getId() == id; }),
                   clientes.end());
}

void Menu::modificarCliente(int id, const string& nuevoNombre, const string& nuevoContacto) {
    auto cliente = buscarCliente(id);
    if (cliente) {
        cliente->setNombre(nuevoNombre);
        cliente->setContacto(nuevoContacto);
    }
}

shared_ptr<Cliente> Menu::buscarCliente(int id) {
    auto it = find_if(clientes.begin(), clientes.end(),
                      [id](const shared_ptr<Cliente>& c) { return c->getId() == id; });
    return (it != clientes.end()) ? *it : nullptr;
}

void Menu::altaCubiculo(int id, const string& ubicacion) {
    auto cubiculo = make_shared<Cubiculo>(id, ubicacion);
    cubiculos.push_back(cubiculo);
}

void Menu::bajaCubiculo(int id) {
    cubiculos.erase(remove_if(cubiculos.begin(), cubiculos.end(),
                              [id](const shared_ptr<Cubiculo>& c) { return c->getId() == id; }),
                    cubiculos.end());
}

void Menu::modificarCubiculo(int id, const string& nuevaUbicacion) {
    auto cubiculo = buscarCubiculo(id);
    if (cubiculo) {
        cubiculo->setUbicacion(nuevaUbicacion);
    }
}

shared_ptr<Cubiculo> Menu::buscarCubiculo(int id) {
    auto it = find_if(cubiculos.begin(), cubiculos.end(),
                      [id](const shared_ptr<Cubiculo>& c) { return c->getId() == id; });
    return (it != cubiculos.end()) ? *it : nullptr;
}

shared_ptr<Alquiler> Menu::buscarAlquiler(int id) {
    auto it = find_if(alquileres.begin(), alquileres.end(),
                      [id](const shared_ptr<Alquiler>& a) { return a->id == id; });
    return (it != alquileres.end()) ? *it : nullptr;
}

vector<shared_ptr<Alquiler>> Menu::listarAlquileresVector() {
    return alquileres;
}

// Método principal para mostrar el menú

void Menu::mostrarMenu() {
    int opcion = -1;
    while (opcion != 0) {
        cout << "\n=== Menu de Gestion de Alquileres ===\n";
        cout << "1. Agregar Cliente\n";
        cout << "2. Agregar Cubiculo\n";
        cout << "3. Registrar Alquiler\n";
        cout << "4. Listar Alquileres\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            agregarCliente();
            break;
        case 2:
            agregarCubiculo();
            break;
        case 3:
            agregarAlquiler();
            break;
        case 4:
            mostrarAlquileres();
            break;
        case 0:
            cout << "Saliendo...\n";
            break;
        default:
            cout << "Opcion no válida.\n";
            break;
        }
    }
}

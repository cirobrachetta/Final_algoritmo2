#include "Menu.hpp"
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

void Menu::mostrarMenu() {
    int opcion = -1;
    while (opcion != 0) {
        cout << "\n=== Menu de Gestion de Alquileres ===\n";
        cout << "1. Agregar Cliente\n";
        cout << "2. Agregar Cubiculo\n";
        cout << "3. Registrar Alquiler\n";
        cout << "4. Listar Clientes\n";
        cout << "5. Listar Cubiculos\n";
        cout << "6. Listar Alquileres\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            int id;
            string nombre, contacto;

            cout << "Ingrese ID del cliente: ";
            cin >> id;
            cin.ignore();

            cout << "Ingrese nombre del cliente: ";
            getline(cin, nombre);

            cout << "Ingrese contacto del cliente: ";
            getline(cin, contacto);

            gestor.altaCliente(id, nombre, contacto);
            cout << "Cliente agregado correctamente.\n";
            break;
        }
        case 2: {
            int id;
            string ubicacion;

            cout << "Ingrese ID del cubiculo: ";
            cin >> id;
            cin.ignore();

            cout << "Ingrese ubicacion del cubiculo: ";
            getline(cin, ubicacion);

            gestor.altaCubiculo(id, ubicacion);
            cout << "Cubiculo agregado correctamente.\n";
            break;
        }
        case 3: {
            int idAlquiler, idCliente;
            vector<int> idsCubiculos;
            string fechaInicio, fechaFin;

            cout << "Ingrese ID del alquiler: ";
            cin >> idAlquiler;

            // Listar clientes disponibles
            auto clientes = gestor.listarClientes();
            if (clientes.empty()) {
                cout << "No hay clientes registrados. Registre un cliente antes de continuar.\n";
                break;
            }
            cout << "\n=== Clientes Disponibles ===\n";
            for (const auto& cliente : clientes) {
                cout << "- ID: " << cliente->getId()
                     << ", Nombre: " << cliente->getNombre()
                     << ", Contacto: " << cliente->getContacto() << "\n";
            }

            cout << "Ingrese ID del cliente: ";
            cin >> idCliente;

            // Listar cubículos disponibles
            auto cubiculos = gestor.listarCubiculos();
            vector<shared_ptr<Cubiculo>> disponibles;
            for (const auto& cubiculo : cubiculos) {
                if (cubiculo->getEstado() == "Disponible") {
                    disponibles.push_back(cubiculo);
                }
            }

            if (disponibles.empty()) {
                cout << "No hay cubiculos disponibles. Registre uno o espere a que se liberen.\n";
                break;
            }
            cout << "\n=== Cubiculos Disponibles ===\n";
            for (const auto& cubiculo : disponibles) {
                cout << "- ID: " << cubiculo->getId()
                     << ", Ubicacion: " << cubiculo->getUbicacion()
                     << "\n";
            }

            int idCubiculo;
            cout << "Ingrese IDs de cubiculos (ingrese -1 para finalizar):\n";
            while (true) {
                cin >> idCubiculo;
                if (idCubiculo == -1) break;

                auto it = find_if(disponibles.begin(), disponibles.end(), [idCubiculo](const auto& cubiculo) {
                    return cubiculo->getId() == idCubiculo;
                });

                if (it != disponibles.end()) {
                    idsCubiculos.push_back(idCubiculo);
                } else {
                    cout << "ID de cubiculo inválida o no disponible. Intente de nuevo.\n";
                }
            }

            cin.ignore();
            cout << "Ingrese fecha de inicio (YYYY-MM-DD): ";
            getline(cin, fechaInicio);

            cout << "Ingrese fecha de fin (YYYY-MM-DD): ";
            getline(cin, fechaFin);

            try {
                gestor.altaAlquiler(idAlquiler, idCliente, idsCubiculos, fechaInicio, fechaFin);
                cout << "Alquiler registrado correctamente.\n";
            } catch (const runtime_error& e) {
                cout << "Error al registrar el alquiler: " << e.what() << "\n";
            }
            break;
        }
        case 4: {
            auto clientes = gestor.listarClientes();
            if (clientes.empty()) {
                cout << "No hay clientes registrados.\n";
            } else {
                cout << "Clientes registrados:\n";
                for (const auto& cliente : clientes) {
                    cout << "- ID: " << cliente->getId()
                         << ", Nombre: " << cliente->getNombre()
                         << ", Contacto: " << cliente->getContacto() << "\n";
                }
            }
            break;
        }
        case 5: {
            auto cubiculos = gestor.listarCubiculos();
            if (cubiculos.empty()) {
                cout << "No hay cubiculos registrados.\n";
            } else {
                cout << "Cubiculos registrados:\n";
                for (const auto& cubiculo : cubiculos) {
                    cout << "- ID: " << cubiculo->getId()
                         << ", Ubicacion: " << cubiculo->getUbicacion()
                         << ", Estado: " << cubiculo->getEstado() << "\n";
                }
            }
            break;
        }
        case 6: {
            auto alquileres = gestor.listarAlquileres();
            if (alquileres.empty()) {
                cout << "No hay alquileres registrados.\n";
            } else {
                cout << "Alquileres registrados:\n";
                for (const auto& alquiler : alquileres) {
                    cout << "- ID: " << alquiler->id
                         << ", Cliente: " << alquiler->cliente->getNombre()
                         << ", Fecha Inicio: " << alquiler->fechaInicio
                         << ", Fecha Fin: " << alquiler->fechaFin << "\n";

                    cout << "  Cubiculos:\n";
                    for (const auto& cubiculo : alquiler->cubiculos) {
                        cout << "    - " << cubiculo->getId() << ": " << cubiculo->getUbicacion() << "\n";
                    }
                }
            }
            break;
        }
        case 0:
            cout << "Saliendo...\n";
            break;
        default:
            cout << "Opcion no válida.\n";
            break;
        }
    }
}

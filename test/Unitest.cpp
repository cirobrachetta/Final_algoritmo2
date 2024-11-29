#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Cliente.hpp"
#include "Cubiculo.hpp"
#include "Alquiler.hpp"
#include "MockMensaje.hpp"
#include "Menu.hpp"

TEST_CASE("Alta, baja y modificación de clientes", "[Menu]") {
    Menu menu;

    SECTION("Alta de cliente") {
        // Agregar un cliente
        menu.altaCliente(1, "Juan Pérez", "123456789");

        // Verificar que el cliente se haya agregado correctamente
        auto cliente = menu.buscarCliente(1);
        REQUIRE(cliente != nullptr);
        REQUIRE(cliente->getNombre() == "Juan Pérez");
        REQUIRE(cliente->getContacto() == "123456789");
    }

    SECTION("Modificación de cliente") {
        // Agregar un cliente y luego modificarlo
        menu.altaCliente(1, "Juan Pérez", "123456789");
        menu.modificarCliente(1, "Juan Modificado", "987654321");

        // Verificar los cambios
        auto cliente = menu.buscarCliente(1);
        REQUIRE(cliente != nullptr);
        REQUIRE(cliente->getNombre() == "Juan Modificado");
        REQUIRE(cliente->getContacto() == "987654321");
    }

    SECTION("Baja de cliente") {
        // Agregar y luego eliminar un cliente
        menu.altaCliente(1, "Juan Pérez", "123456789");
        menu.bajaCliente(1);

        // Verificar que el cliente ya no existe
        auto cliente = menu.buscarCliente(1);
        REQUIRE(cliente == nullptr);
    }
}

TEST_CASE("Alta, baja y modificación de cubículos", "[Menu]") {
    Menu menu;

    SECTION("Alta de cubículo") {
        // Agregar un cubículo
        menu.altaCubiculo(1, "Zona A");

        // Verificar que el cubículo se haya agregado correctamente
        auto cubiculo = menu.buscarCubiculo(1);
        REQUIRE(cubiculo != nullptr);
        REQUIRE(cubiculo->getUbicacion() == "Zona A");
    }

    SECTION("Modificación de cubículo") {
        // Agregar un cubículo y luego modificarlo
        menu.altaCubiculo(1, "Zona A");
        menu.modificarCubiculo(1, "Zona B");

        // Verificar los cambios
        auto cubiculo = menu.buscarCubiculo(1);
        REQUIRE(cubiculo != nullptr);
        REQUIRE(cubiculo->getUbicacion() == "Zona B");
    }

    SECTION("Baja de cubículo") {
        // Agregar y luego eliminar un cubículo
        menu.altaCubiculo(1, "Zona A");
        menu.bajaCubiculo(1);

        // Verificar que el cubículo ya no existe
        auto cubiculo = menu.buscarCubiculo(1);
        REQUIRE(cubiculo == nullptr);
    }
}

TEST_CASE("Alta y listado de alquileres", "[Menu]") {
    Menu menu;

    // Crear un cliente y un cubículo
    menu.altaCliente(1, "Juan Pérez", "123456789");
    menu.altaCubiculo(1, "Zona A");

    SECTION("Alta de alquiler") {
        // Crear un alquiler
        menu.altaAlquiler(1, 1, {1}, "2024-11-01", "2024-12-01");

        // Verificar que el alquiler se haya creado correctamente
        auto alquiler = menu.buscarAlquiler(1);
        REQUIRE(alquiler != nullptr);
        REQUIRE(alquiler->cliente->getId() == 1);
        REQUIRE(alquiler->cubiculos.size() == 1);
        REQUIRE(alquiler->cubiculos[0]->getId() == 1);
    }

    SECTION("Listado de alquileres") {
        // Crear un alquiler
        menu.altaAlquiler(1, 1, {1}, "2024-11-01", "2024-12-01");

        // Listar alquileres
        auto alquileres = menu.listarAlquileres();

        // Verificar que el alquiler esté en la lista
        REQUIRE(alquileres.size() == 1);
        REQUIRE(alquileres[0]->cliente->getId() == 1);
        REQUIRE(alquileres[0]->cubiculos.size() == 1);
        REQUIRE(alquileres[0]->cubiculos[0]->getId() == 1);
    }
}

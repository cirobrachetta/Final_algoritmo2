#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "GestorAlquileres.hpp"
#include "MockMensaje.hpp"

TEST_CASE("Gestión de clientes", "[GestorAlquileres]") {
    GestorAlquileres gestor;

    SECTION("Alta de cliente") {
        gestor.altaCliente(1, "Juan Perez", "123456789");

        auto clientes = gestor.listarClientes();
        REQUIRE(clientes.size() == 1);
        REQUIRE(clientes[0]->getNombre() == "Juan Perez");
        REQUIRE(clientes[0]->getContacto() == "123456789");
    }

    SECTION("Modificación de cliente") {
        gestor.altaCliente(1, "Juan Perez", "123456789");
        gestor.modificarCliente(1, "Juan Modificado", "987654321");

        auto clientes = gestor.listarClientes();
        REQUIRE(clientes[0]->getNombre() == "Juan Modificado");
        REQUIRE(clientes[0]->getContacto() == "987654321");
    }

    SECTION("Baja de cliente") {
        gestor.altaCliente(1, "Juan Perez", "123456789");
        gestor.bajaCliente(1);

        auto clientes = gestor.listarClientes();
        REQUIRE(clientes.empty());
    }
}

TEST_CASE("Gestión de cubículos", "[GestorAlquileres]") {
    GestorAlquileres gestor;

    SECTION("Alta de cubículo") {
        gestor.altaCubiculo(1, "Zona A");

        auto cubiculos = gestor.listarCubiculos();
        REQUIRE(cubiculos.size() == 1);
        REQUIRE(cubiculos[0]->getUbicacion() == "Zona A");
    }

    SECTION("Modificación de cubículo") {
        gestor.altaCubiculo(1, "Zona A");
        gestor.modificarCubiculo(1, "Zona B", "Disponible");

        auto cubiculos = gestor.listarCubiculos();
        REQUIRE(cubiculos[0]->getUbicacion() == "Zona B");
    }

    SECTION("Baja de cubículo") {
        gestor.altaCubiculo(1, "Zona A");
        gestor.bajaCubiculo(1);

        auto cubiculos = gestor.listarCubiculos();
        REQUIRE(cubiculos.empty());
    }
}

TEST_CASE("Gestión de alquileres con notificaciones", "[GestorAlquileres][MockMensaje]") {
    GestorAlquileres gestor;
    MockMensaje mockMensaje;

    // Crear un cliente y un cubículo
    gestor.altaCliente(1, "Juan Perez", "123456789");
    gestor.altaCubiculo(1, "Zona A");

    SECTION("Alta de alquiler con notificación") {
        gestor.altaAlquiler(1, 1, {1}, "2024-11-01", "2024-12-01");
        mockMensaje.enviarMensaje(*gestor.listarClientes()[0], "Alquiler registrado");

        // Verificar que el alquiler se registró y se envió la notificación
        auto alquileres = gestor.listarAlquileres();
        REQUIRE(alquileres.size() == 1);
        REQUIRE(alquileres[0]->cliente->getId() == 1);
        REQUIRE(alquileres[0]->cubiculos[0]->getId() == 1);
        REQUIRE(mockMensaje.mensajeEnviado);
    }

    SECTION("Baja de alquiler") {
        gestor.altaAlquiler(1, 1, {1}, "2024-11-01", "2024-12-01");
        gestor.bajaAlquiler(1);

        auto alquileres = gestor.listarAlquileres();
        REQUIRE(alquileres.empty());
    }

    SECTION("Listado de alquileres") {
        gestor.altaAlquiler(1, 1, {1}, "2024-11-01", "2024-12-01");

        auto alquileres = gestor.listarAlquileres();
        REQUIRE(alquileres.size() == 1);
        REQUIRE(alquileres[0]->fechaInicio == "2024-11-01");
        REQUIRE(alquileres[0]->fechaFin == "2024-12-01");
    }
}

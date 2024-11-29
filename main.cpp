#include "Menu.hpp"
#include <memory>
#include "Cliente.hpp"
#include "Cubiculo.hpp"
#include "Mensaje.hpp"
#include "Alquiler.hpp"

int main() {
    auto cliente = make_shared<Cliente>(1, "Juan Perez", "+123456789");
    auto cubiculo = make_shared<Cubiculo>(101, "Sector A");

    auto notificador = make_shared<MensajeWhatsApp>();
    Alquiler alquiler(1, cliente, notificador);

    alquiler.agregarCubiculo(cubiculo);
    alquiler.fechaInicio = "2024-11-01";
    alquiler.fechaFin = "2024-11-30";

    alquiler.notificar();

    Menu menu;
    menu.mostrarMenu();

    return 0;
}

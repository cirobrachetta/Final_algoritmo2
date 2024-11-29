#include "Alquiler.hpp"

Alquiler::Alquiler(int id, shared_ptr<Cliente> cliente, shared_ptr<Mensaje> notificador)
    : id(id), cliente(move(cliente)), metodoNotificacion(move(notificador)) {}

void Alquiler::agregarCubiculo(const shared_ptr<Cubiculo>& cubiculo) {
    cubiculos.push_back(cubiculo);
    cubiculo->getEstado() = "Alquilado";
}

void Alquiler::notificar() {
    metodoNotificacion->enviarMensaje(*cliente, "Su alquiler vence el " + fechaFin);
}

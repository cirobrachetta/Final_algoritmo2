#include "Mensaje.hpp"

void MensajeWhatsApp::enviarMensaje(const Cliente& cliente, const string& mensaje) {
    cout << "[WhatsApp] Enviando a " << cliente.getContacto() << ": " << mensaje << endl;
}

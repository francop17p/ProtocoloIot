#include <iostream>
#include "IoTProtocol.h"

int main() {
    // Dirección IP y puerto del servidor
    std::string server_ip = "127.0.0.1";  // Cambia esta IP por la de tu servidor
    int server_port = 1883;                   // Cambia el puerto si es necesario

    // Crear el objeto IoTProtocol
    IoTProtocol protocol(server_ip, server_port);

    // Conectar al servidor
    if (!protocol.connectToServer()) {
        std::cerr << "No se pudo conectar al servidor" << std::endl;
        return 1;
    }

    // Enviar datos (por ejemplo, temperatura)
    std::string data = "Temperatura: 23.5 C";  // Datos que quieras enviar
    if (!protocol.sendData(data)) {
        std::cerr << "Error al enviar datos" << std::endl;
        return 1;
    }

    std::cout << "Datos enviados correctamente" << std::endl;
    protocol.disconnect();

    return 0;
}

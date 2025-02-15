#include "IoTProtocol.h"
#include <iostream>
#include <cstring>

#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#endif

IoTProtocol::IoTProtocol(const std::string& server_ip, int server_port)
    : server_ip(server_ip), server_port(server_port), is_connected(false) {

#ifdef _WIN32
    // Inicialización de Winsock para Windows
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Error al iniciar Winsock" << std::endl;
    }
#endif

    // Crear socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Error al crear el socket" << std::endl;
    }
}

IoTProtocol::~IoTProtocol() {
    disconnect();
#ifdef _WIN32
    WSACleanup();
#endif
}

bool IoTProtocol::connectToServer() {
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    server_addr.sin_addr.s_addr = inet_addr(server_ip.c_str());

    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Error al conectar con el servidor" << std::endl;
        return false;
    }

    is_connected = true;
    return true;
}

bool IoTProtocol::sendData(const std::string& data) {
    if (!is_connected) {
        std::cerr << "No está conectado al servidor" << std::endl;
        return false;
    }

    if (send(sock, data.c_str(), data.size(), 0) < 0) {
        std::cerr << "Error al enviar datos" << std::endl;
        return false;
    }

    std::cout << "Datos enviados: " << data << std::endl;
    return true;
}

void IoTProtocol::disconnect() {
    if (is_connected) {
#ifdef _WIN32
        closesocket(sock);  // En Windows, se usa closesocket()
#else
        close(sock);        // En Linux/macOS, se usa close()
#endif
        is_connected = false;
    }
}



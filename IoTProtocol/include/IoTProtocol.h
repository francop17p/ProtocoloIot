#ifndef IOTPROTOCOL_H
#define IOTPROTOCOL_H

#ifdef _WIN32
#include <winsock2.h>
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#endif
#include <string>

class IoTProtocol {
public:
    // Constructor y destructor
    IoTProtocol(const std::string& server_ip, int server_port);
    ~IoTProtocol();

    // Métodos públicos
    bool connectToServer();     // Conectar al servidor
    bool sendData(const std::string& data); // Enviar datos
    void disconnect();          // Desconectar

private:
    std::string server_ip;
    int server_port;
    int sock;
    bool is_connected;

#ifdef _WIN32
    WSADATA wsaData;
#endif
};

#endif // IOTPROTOCOL_H

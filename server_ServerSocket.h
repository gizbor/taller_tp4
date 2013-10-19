#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H
#include "common_General.h"
#include "common_Socket.h"
#include <string>

#define MAX_COLA_ESPERA 5

class ServerSocket: public Socket
{
    public:
        ServerSocket();
        explicit ServerSocket(t_puerto puerto) { setPuerto(puerto); }
        virtual ~ServerSocket();

        int conectar();

        int getSocketPuerto() { return this->socket_puerto; }
        void setSocketPuerto(int socket) { this->socket_puerto=socket; }

        void imprimir();
        int aceptar();
        void cancelar();

        void apagar();
        std::string aString();
    protected:
    private:
        int socket_puerto;
};

#endif // SERVERSOCKET_H

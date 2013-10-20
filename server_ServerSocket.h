#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H
#include "common_General.h"
#include "common_Socket.h"
#include "common_Listener.h"
#include <string>
#define MAX_COLA_ESPERA 5

class ServerSocket: public Socket
{
    public:
        ServerSocket(Listener* listener);
        explicit ServerSocket(t_puerto puerto) { setPuerto(puerto); }
        virtual ~ServerSocket();

        int conectar();

        int getSocketPuerto() { return this->socket_puerto; }
        void setSocketPuerto(int socket) { this->socket_puerto=socket; }
        void setListener(Listener* listener) { this->listener=listener; }

        void* run();

        void imprimir();
        int aceptar();
        void cancelar();

        void apagar();
        std::string aString();
    protected:
    private:
        Listener* listener;
        int socket_puerto;

};

#endif // SERVERSOCKET_H

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
        /////////int abrir(t_puerto puerto);
        int conectar();

        int getSocketPuerto() { return this->socket_puerto; }
        void setSocketPuerto(int socket) { this->socket_puerto=socket; }
      //  void cerrar();
       // void apagar();
       // t_puerto getPuerto() { return this->puerto; }
       // int getSocket() { return this->socketfd; }
       // void setPuerto(t_puerto puerto) { this->puerto= puerto; }
        void imprimir();
        int aceptar();
        void cancelar();
     //   int recibir(char** mensaje);
       // int enviar(const char* mensaje, uint32_t tamanio);
       void apagar();
        std::string aString();
    protected:
    private:
        int socket_puerto;
       // t_puerto puerto;
};

#endif // SERVERSOCKET_H

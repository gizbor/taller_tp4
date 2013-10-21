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
        explicit ServerSocket(Listener* listener);
        explicit ServerSocket(t_puerto puerto) { setPuerto(puerto); }
        virtual ~ServerSocket();
        /** Descripcion: conecta el socket.
        *   POS: el socket queda en estado "listen" en caso de exito.
        *   Retorno: 1 -> error, 0 -> exito
        */
        int conectar();
        /** Getters y Setters */
        int getSocketPuerto() { return this->socket_puerto; }
        void setSocketPuerto(int socket) { this->socket_puerto=socket; }
        void setListener(Listener* listener) { this->listener=listener; }

        /** Descripcion: acepta conexiones entrantes hasta un maximo de 
        *   MAX_COLA_ESPERA hasta que el puerto sea apagado.
        *   PRE: puerto conectado.
        *   Retorno: -1 -> error, 0 -> exito
        */
        void* run();

        void imprimir();
        int aceptar();
        /** Descripcion: cierra ultima conexion entrante aceptada.
        *   Retorno: -
        */
        void cancelar();

        void apagar();
        std::string aString();
    protected:
    private:
        Listener* listener;
        int socket_puerto;
};

#endif // SERVERSOCKET_H

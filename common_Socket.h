#ifndef COMMON_SOCKET_H_INCLUDED
#define COMMON_SOCKET_H_INCLUDED
#include "common_General.h"
#include "common_Thread.h"
#include <string>
class Socket: public Thread
{
    public:
        Socket();
        ~Socket();
        /* Getters y Setters */
        t_puerto getPuerto() { return this->puerto; }
        int getSocket() { return this->socketfd; }
        std::string getDireccion() { return this->direccion; }
        void setSocket(int socketfd) { this->socketfd = socketfd; }
        void setPuerto(t_puerto puerto=-1) { this->puerto= puerto; }
        void setDireccion(std::string direccion) { this->direccion= direccion; }
        /** Descripcion: recibe en "buffer" mensaje enviado por cliente.
        *   Retorno: -1 -> error, >0 -> exito: cant. bytes recibidos
        */
        virtual int recibir(char** buffer);
        /** Descripcion: envia "mensaje" de tamanio "tamanio".
        *   Retorno: -1 -> error, >0 -> exito: cant. bytes enviados
        */
        virtual int enviar(char* mensaje, uint32_t tamanio);
        virtual int conectar() = 0;

        virtual void* run() = 0;

        void cerrar();
        void apagar();
        virtual std::string aString();

        void imprimir();
        bool estaConectado();
        /** Descripcion: setea estructuras necesarias para conexion.
        *   Retorno: 1 -> error, 0 -> exito
        */
        int setAddrInfo();
        /** Descripcion: obtiene un file descriptor para el socket y lo 
        *   setea en atributo "socketfd" en caso de exito.
        *   PRE: debio ejecutarse setAddrInfo previamente.
        *   Retorno: 1 -> error, 0 -> exito
        */
        int getSocketDescriptor();
    protected:
        struct addrinfo host_info;
        struct addrinfo *host_info_list;
    private:
        int socketfd;
        t_puerto puerto;
        std::string direccion;
};

#endif // COMMON_SOCKET_H_INCLUDED

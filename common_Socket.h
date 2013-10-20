#ifndef COMMON_SOCKET_H_INCLUDED
#define COMMON_SOCKET_H_INCLUDED
#include "common_General.h"
#include "common_Thread.h"
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

        virtual int recibir(char** buffer);
        virtual int enviar(char* mensaje, uint32_t tamanio);
        virtual int conectar() = 0;
        virtual void* run() = 0;

        void cerrar();
        void apagar();
        virtual std::string aString();

        void imprimir();
        bool estaConectado();

        int setAddrInfo();
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

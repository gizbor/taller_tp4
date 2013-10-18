#ifndef COMMON_SOCKET_H_INCLUDED
#define COMMON_SOCKET_H_INCLUDED
#include "common_General.h"
class Socket
{
    public:
        Socket();
        ~Socket();
        /* Getters y Setters */
        t_puerto getPuerto() { return this->puerto; }
        int getSocket() { return this->socketfd; }
        void setSocket(int socketfd) { this->socketfd = socketfd; }
        void setPuerto(t_puerto puerto=-1) { this->puerto= puerto; }

        virtual int recibir(char** buffer);
        virtual int enviar(char* mensaje, uint32_t tamanio);

        void cerrar();
        void apagar();
        virtual std::string aString();

        void imprimir();
        bool estaConectado();
    protected:
    private:
        int socketfd;
        t_puerto puerto;
};

//        SERVER
//        int abrir(t_puerto puerto);
//
//        int aceptar();
//        void cancelar();

//    protected:
//    private:
//        int socket_aceptado;


//  CLIENTE
//      void setDireccion(std::string direccion) { this->direccion = direccion; }
//      int conectar();
//      void desconectar();
//
//  protected:
//  private:
//      std::string direccion;

#endif // COMMON_SOCKET_H_INCLUDED

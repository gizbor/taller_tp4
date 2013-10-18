#ifndef CLIENTE_H
#define CLIENTE_H
#include "client_ClientSocket.h"
#include "common_funciones.h"
#include "common_General.h"
#include <string>

class Cliente
{
    public:
        Cliente(std::string direccion,t_puerto puerto);
        virtual ~Cliente();
        int conectar();
        void desconectar();
        int enviar(const char* msg, uint32_t tamanio);
        int recibir(char** msg, uint32_t& tamanio);
    protected:
    private:
        ClientSocket osocket;
};

#endif // CLIENTE_H

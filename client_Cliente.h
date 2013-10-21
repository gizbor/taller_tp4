#ifndef CLIENTE_H
#define CLIENTE_H
#include "client_ClientSocket.h"
#include "common_General.h"
#include "common_Protocolo.h"
#include <string>

class Cliente{
    public:
        explicit Cliente(std::string direccion_puerto);
        virtual ~Cliente();
        /** Descripcion: se conecta al servidor.
          *    Retorno: 0 -> conectado, 1->error
          */
        int conectar();
        /** Descripcion: se desconecta al servidor.
          */
        void desconectar();
        /** Descripcion: envia cadena de caracteres "msg" de tamanio "tamanio"
          * al servidor.
          * Retorno: 0 -> enviado con exito, 1->hubo un error
          */
        int enviar(const char* msg, uint32_t tamanio);
        /** Descripcion: recibe en "msg" el mensaje enviado por servidor de
          * tamanio "tamanio".
          * Retorno: 0 -> recibido con exito, 1->hubo un error
          */
        int recibir(char** msg, uint32_t& tamanio);
        /** Descripcion: envia el contenido del archivo pasado por parametro
          * al servidor.
          * Retorno: 0 -> enviado con exito, 1-> hubo un error
          */
        int transmitirArchivo(std::ifstream& archivo);

    private:
        ClientSocket osocket;
        Protocolo protocolo;
        /** Descripcion: recibe string con formato DIRECCION_IP:PUERTO y copia
          *   en los parametros pasados por referencia los dos valores por separado.
          *   Retorno: -
          */
        void getDireccionYPuerto(char const * dir_puerto, \
                                                        std::string& direccion,\
                                                        t_puerto& puerto);
};

#endif // CLIENTE_H

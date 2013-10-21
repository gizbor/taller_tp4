#ifndef SERVIDOR_H
#define SERVIDOR_H
#include "common_General.h"
#include "server_ServerSocket.h"
#include "common_Protocolo.h"
#include "common_Listener.h"
#include <string>
#include <vector>

class ApagaServidor;
class Servidor: public Listener {
    public:
        Servidor();
        virtual ~Servidor();

        void setApagador(ApagaServidor* apagador) { this->apagador=apagador; }
        /** Descripcion: abre el puerto especificado y lo agrega a lista de 
        *   puertos en caso de exito.
        *   Retorno: 1 -> error, 0 -> exito
        */
        int abrir(t_puerto puerto);
        /** Descripcion: cierra todos los puertos abiertos con exito.
        *   Retorno: -
        */
        void cerrar();

        /** Descripcion: recibe el archivo del cliente. Ademas se encarga de 
        *   enviar mensajes de confirmacion de conexion y recepcion de datos.
        *   Retorno: 1 -> error, 0 -> exito
        */
        int atender(Socket& socket);

        int enviar(char* mensaje, uint32_t tamanio);

        bool estaAbierto(t_puerto puerto);

        int enviarConfirmacionArchivo(ServerSocket& socket, uint32_t tamanio);
        int confirmarConexion(ServerSocket& socket);
        int recibirArchivo(ServerSocket& socket, char** buffer_entrada);

        /** Descripcion: administra los puertos ejecutando los hilos necesarios
        *   para aceptar conexiones entrantes.
        *   PRE: puertos abiertos y apagador seteado.
        *   Retorno: cantidad de puertos abiertos con exito.
        */
        int iniciar(std::string puertos);
        /** Descripcion: apaga los puertos en escucha permitiendo terminar de 
        *   procesar las comunicaciones establecidas.
        *   Retorno: -
        */
        void apagar();

    protected:
        /** Descripcion: imprime por pantalla los distintos mensajes de log.
        *   Retorno: -
        */
        static void loguear(const std::string& mensaje);
        
    private:
        ServerSocket* getSocket(t_puerto puerto);
        std::vector<ServerSocket*> puertos;
        static pthread_mutex_t log_mutex;
        
        ApagaServidor* apagador;
        void parsearPuertos(const char* puertos, \
                        std::vector<t_puerto> &vpuertos);
        static Protocolo protocolo;        
};

#endif // SERVIDOR_H

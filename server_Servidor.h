#ifndef SERVIDOR_H
#define SERVIDOR_H
#include "common_General.h"
#include <vector>
#include <map>
#include "server_ServerSocket.h"
#include "common_funciones.h"
#include "common_Protocolo.h"
#include <string>

class Servidor {
    public:
        Servidor();
        virtual ~Servidor();

        int abrir(t_puerto puerto);
        void cerrar();

        static void* aceptar(void* v_puerto);
        static int enviar(char* mensaje, uint32_t tamanio);

        pthread_t escuchar(t_puerto puerto);
        bool estaAbierto(t_puerto puerto);
        pthread_t apagador();

        static int enviarConfirmacionArchivo(ServerSocket& socket, uint32_t tamanio);
        static int confirmarConexion(ServerSocket& socket);
        static int recibirArchivo(ServerSocket& socket, char** buffer_entrada);


        int iniciar(std::string puertos);

    protected:
    private:
        ServerSocket* getSocket(t_puerto puerto);
        std::vector<ServerSocket*> puertos;
        static pthread_mutex_t log_mutex;
        static void loguear(const std::string& mensaje);
        static void* salir(void*arg);
        static void apagar(std::vector<ServerSocket*> &puertos);
        void parsearPuertos(const char* puertos, std::vector<t_puerto> &vpuertos);
        static Protocolo protocolo;
};

#endif // SERVIDOR_H

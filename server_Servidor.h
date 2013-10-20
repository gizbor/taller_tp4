#ifndef SERVIDOR_H
#define SERVIDOR_H
#include "common_General.h"
#include "server_ServerSocket.h"
#include "common_Protocolo.h"
#include "common_Listener.h"
#include <string>

class ApagaServidor;
class Servidor: public Listener {
    public:
        Servidor();
        virtual ~Servidor();

        void setApagador(ApagaServidor* apagador) { this->apagador=apagador; }

        int abrir(t_puerto puerto);
        void cerrar();

        int atender(Socket& socket);
        int enviar(char* mensaje, uint32_t tamanio);

        bool estaAbierto(t_puerto puerto);

        int enviarConfirmacionArchivo(ServerSocket& socket, uint32_t tamanio);
        int confirmarConexion(ServerSocket& socket);
        int recibirArchivo(ServerSocket& socket, char** buffer_entrada);

        int iniciar(std::string puertos);

        void apagar();
    protected:
    private:
        ServerSocket* getSocket(t_puerto puerto);
        std::vector<ServerSocket*> puertos;
        static pthread_mutex_t log_mutex;
        static void loguear(const std::string& mensaje);
        ApagaServidor* apagador;

        void parsearPuertos(const char* puertos, std::vector<t_puerto> &vpuertos);
        static Protocolo protocolo;
};

#endif // SERVIDOR_H

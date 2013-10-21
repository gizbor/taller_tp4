#ifndef APAGASERVIDOR_H
#define APAGASERVIDOR_H
#include "common_Thread.h"
#include "common_General.h"
#include "server_Servidor.h"
class ApagaServidor: public Thread
{
    public:
        explicit ApagaServidor(Servidor* servidor);
        virtual ~ApagaServidor();
        void setServidor(Servidor* servidor) { this->servidor=servidor; }
        /** Descripcion: escucha teclado y ejecuta el metodo "apagar" del 
        *	servidor al presionar "q".
        *   Retorno: -
        */
        void* run();
    protected:
    private:
        Servidor* servidor;
};

#endif // APAGASERVIDOR_H

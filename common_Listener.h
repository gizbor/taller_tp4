#ifndef LISTENER_H
#define LISTENER_H
#include "common_Socket.h"

class Listener
{
    public:
        Listener() {}
        virtual ~Listener() {}
        /** Descripcion: despacha al objeto Listener el puerto aceptado 
          * para comunicarse mediante el mismo.
          * Retorno: 0 -> proceso terminado con exito, 1-> hubo un error
          */
        virtual int atender(Socket& socket) = 0;
    protected:
    private:
};

#endif // LISTENER_H

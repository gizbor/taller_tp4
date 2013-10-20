#ifndef LISTENER_H
#define LISTENER_H
#include "common_Socket.h"

class Listener
{
    public:
        Listener() {};
        virtual ~Listener() {};
        virtual int atender(Socket& socket) = 0;
    protected:
    private:
};

#endif // LISTENER_H

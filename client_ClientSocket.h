#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H
#include "common_General.h"
#include "common_Socket.h"
#include <string>

class ClientSocket: public Socket
{
  public:
      ClientSocket();
      virtual ~ClientSocket();
      int conectar();
      std::string aString();
      void* run(){ return 0; }
  protected:
  private:

};

#endif // CLIENTSOCKET_H

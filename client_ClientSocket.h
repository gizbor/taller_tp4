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
      //void setPuerto(t_puerto puerto=-1) { this->puerto= puerto; }
      //t_puerto getPuerto() { return this->puerto; }
      void setDireccion(std::string direccion) { this->direccion = direccion; }
      //int recibir(char** buffer);
      //int enviar(char* mensaje, uint32_t tamanio);
      int conectar();
      //void desconectar();
      //bool estaConectado();
      std::string aString();
  protected:
     // int getSocket() { return this->socketd; }
  private:

      std::string direccion;

};

#endif // CLIENTSOCKET_H

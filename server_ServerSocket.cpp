#include "server_ServerSocket.h"
#include <string>

ServerSocket::ServerSocket(Listener* listener){
    setSocketPuerto(PUERTO_NO_ABIERTO);
    setListener(listener);
}

ServerSocket::~ServerSocket(){
}

int ServerSocket::conectar(){
    int estado;
    int error=1;
    int socketd;

    if (setAddrInfo()==0) {
        if ((socketd = getSocketDescriptor())!=-1){
            int yes = 1;
            estado = setsockopt(socketd, SOL_SOCKET, \
                                               SO_REUSEADDR, &yes, sizeof(int));
            estado = bind(socketd, host_info_list->ai_addr, \
                                     host_info_list->ai_addrlen);
            if (estado == -1) {
                DEBUG_MSG("Error en el bind.");
            }  else {
                estado =  listen(socketd, MAX_COLA_ESPERA);
                if (estado == -1){
                    DEBUG_MSG("Error en el listen.");
                } else {
                    setSocketPuerto(socketd);
                    error=0;
                }
            }
        }
    }
return error;
}

void ServerSocket::imprimir(){
    std::cout << this->aString() << std::endl;
}

void ServerSocket::cancelar(){
 if (getSocket()!=PUERTO_NO_ABIERTO){
    close(getSocket());
    setSocket(PUERTO_NO_ABIERTO);
 }
}

void* ServerSocket::run(){
  int  new_sd;
  struct sockaddr_storage their_addr;
  bool shutdown=false;
  int error=-1;
  socklen_t addr_size = sizeof(their_addr);
  if (this->getSocketPuerto()!=PUERTO_NO_ABIERTO){
    while (!shutdown){
      new_sd = accept(getSocketPuerto(), \
                     (struct sockaddr *)&their_addr, \
                      &addr_size);
      if (new_sd == -1){
         DEBUG_MSG("Error en el aceptar.");
         shutdown=true;
      } else {
            setSocket(new_sd);
            this->listener->atender(*this);
            this->cancelar();
      }
      error=0;
    }
  }
  this->kill();
return (void*)error;
}

void ServerSocket::apagar(){
	shutdown(getSocketPuerto(), 2);
}

std::string ServerSocket::aString(){
    std::stringstream s;
    s << "Puerto: " << getPuerto() << ", Socket Server: " << getSocketPuerto();
return s.str();
}

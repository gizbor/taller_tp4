#include "server_ServerSocket.h"
#include <string>

ServerSocket::ServerSocket(){
    setSocketPuerto(PUERTO_NO_ABIERTO);
}

ServerSocket::~ServerSocket(){
}


//int ServerSocket::abrir(t_puerto puerto){
//    int status;
//    struct addrinfo host_info;
//    struct addrinfo *host_info_list;
//    int error=0;
//    int socketd;
//    memset(&host_info, 0, sizeof host_info);
//
//    host_info.ai_family = AF_UNSPEC;
//    host_info.ai_socktype = SOCK_STREAM;
//    host_info.ai_flags = AI_PASSIVE;
//
//    std::stringstream puerto_str;
//    puerto_str << puerto;
//    status = getaddrinfo(NULL,puerto_str.str().c_str(), \
//                         &host_info, &host_info_list);
//    if (status != 0) {
//        DEBUG_MSG("Error en getaddrinfo.");
//        error= -1;
//    } else {
//        socketd = socket(host_info_list->ai_family,   \
//                                host_info_list->ai_socktype, \
//                                host_info_list->ai_protocol);
//        if (socketd == -1){
//            DEBUG_MSG("Error en socket.");
//            error=-2;
//        } else {
//            int yes = 1;
//            status = setsockopt(socketd, SOL_SOCKET, \
//                                SO_REUSEADDR, &yes, sizeof(int));
//
//            status = bind(socketd, host_info_list->ai_addr, \
//                          host_info_list->ai_addrlen);
//            if (status == -1) {
//                DEBUG_MSG("Error en el bind.");
//                error= -3;
//            }  else {
//                status =  listen(socketd, MAX_COLA_ESPERA);
//                if (status == -1){
//                    error= -4;
//                    DEBUG_MSG("Error en el listen.");
//                } else {
//                    setSocketPuerto(socketd);
//                    setPuerto(puerto);
//                }
//            }
//        }
//    }
//    freeaddrinfo(host_info_list);
//return error;
//}

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

/*PRE: puerto abierto */
int ServerSocket::aceptar(){
  int error=0, new_sd;
  struct sockaddr_storage their_addr;
  socklen_t addr_size = sizeof(their_addr);
  if (this->getSocketPuerto()==PUERTO_NO_ABIERTO){
      error= -1;
  } else {
      new_sd = accept(getSocketPuerto(), (struct sockaddr *)&their_addr, &addr_size);
      if (new_sd == -1){
         DEBUG_MSG("Error en el aceptar.");
         error=-1;
      } else {
//          this->socket_aceptado=new_sd;
            setSocket(new_sd);
      }
  }
return error;
}

void ServerSocket::apagar(){
	shutdown(getSocketPuerto(), 2);
}

std::string ServerSocket::aString(){
    std::stringstream s;
    s << "Puerto: " << getPuerto() << ", Socket Server: " << getSocketPuerto();
return s.str();
}



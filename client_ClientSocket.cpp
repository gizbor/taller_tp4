#include "client_ClientSocket.h"
#include <string>

ClientSocket::ClientSocket(){
    this->setSocket(PUERTO_NO_ABIERTO);
}

ClientSocket::~ClientSocket(){
}

std::string ClientSocket::aString(){
    std::stringstream s;
    s << "Puerto: " << getPuerto() << ", Direccion " << \
         direccion<<", Socket: " << getSocket() ;
return s.str();
}

int ClientSocket::conectar(){
    int status;
    int error=0;
    int socketd;
    struct addrinfo host_info;
    struct addrinfo *host_info_list;
    std::stringstream puerto_str;
    puerto_str << getPuerto();
    memset(&host_info, 0, sizeof host_info);
    host_info.ai_family = AF_UNSPEC;
    host_info.ai_socktype = SOCK_STREAM;
    status = getaddrinfo(direccion.c_str(), puerto_str.str().c_str(),\
                         &host_info, &host_info_list);
    if (status!=0){
        DEBUG_MSG("Error en getaddrinfo");
        error=-1;
    } else {
        socketd = socket(host_info_list->ai_family, \
                host_info_list->ai_socktype,host_info_list->ai_protocol);
        if (socketd == -1){
            DEBUG_MSG("socket error ");
            error=-2;
        } else {
            status = connect(socketd, host_info_list->ai_addr, \
                             host_info_list->ai_addrlen);
            if (status == -1){
                DEBUG_MSG("Error conectando!");
                error=-3;
            } else {
                setSocket(socketd);
            }
        }
    }
    freeaddrinfo(host_info_list);
return error;
}





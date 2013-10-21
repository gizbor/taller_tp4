#include "client_ClientSocket.h"
#include <string>

ClientSocket::ClientSocket(){
}

ClientSocket::~ClientSocket(){
}

std::string ClientSocket::aString(){
    std::stringstream s;
    s << "Puerto: " << getPuerto() << ", Direccion " << \
         getDireccion() <<", Socket: " << getSocket();
return s.str();
}

int ClientSocket::conectar(){
    int estado;
    int error=1;
    int socketd;

    if (setAddrInfo()!=1){
        if ((socketd = getSocketDescriptor())!=-1){
            estado = connect(socketd, host_info_list->ai_addr, \
                                           host_info_list->ai_addrlen);
            if (estado == -1){
                DEBUG_MSG("Error conectando!");
            } else {
                setSocket(socketd);
                error=0;
            }
        }
    }
return error;
}




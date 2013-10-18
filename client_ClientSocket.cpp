#include "client_ClientSocket.h"
#include <string>

ClientSocket::ClientSocket(){
}

ClientSocket::~ClientSocket(){
}

std::string ClientSocket::aString(){
    std::stringstream s;
    s << "Puerto: " << getPuerto() << ", Direccion " << \
         getDireccion() <<", Socket: " << getSocket() ;
return s.str();
}


//int ServerSocket::abrir(t_puerto puerto){
//    int status;
//    struct addrinfo host_info;
//    struct addrinfo *host_info_list;
//    int error=0;
//    int socketd;
//    memset(&host_info, 0, sizeof host_info);
//    host_info.ai_family = AF_UNSPEC;
//    host_info.ai_socktype = SOCK_STREAM;
//    host_info.ai_flags = AI_PASSIVE;
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

//int ClientSocket::conectar(){
//    int status;
//    int error=0;
//    int socketd;
//
//    std::stringstream puerto_str;
//    puerto_str << getPuerto();
//    memset(&host_info, 0, sizeof host_info);
//    host_info.ai_family = AF_UNSPEC;
//    host_info.ai_socktype = SOCK_STREAM;
//    status = getaddrinfo(direccion.c_str(), puerto_str.str().c_str(),\
//                         &host_info, &host_info_list);
//    if (status!=0){
//        DEBUG_MSG("Error en getaddrinfo");
//        error=-1;
//    } else {
//        socketd = socket(host_info_list->ai_family, \
//                host_info_list->ai_socktype,host_info_list->ai_protocol);
//        if (socketd == -1){
//            DEBUG_MSG("socket error ");
//            error=-2;
//        } else {
//            status = connect(socketd, host_info_list->ai_addr, \
//                             host_info_list->ai_addrlen);
//            if (status == -1){
//                DEBUG_MSG("Error conectando!");
//                error=-3;
//            } else {
//                setSocket(socketd);
//            }
//        }
//    }
//return error;
//}

// 1: error, 0: no error
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




#include "common_Socket.h"
#include <string>

Socket::Socket(){
    setSocket(SOCKET_NO_ABIERTO);
    setPuerto(PUERTO_NO_ABIERTO);
    setDireccion("");
    host_info_list= NULL;
    memset(&host_info, 0, sizeof host_info);
}

Socket::~Socket(){
    freeaddrinfo(host_info_list);
}

int Socket::setAddrInfo(){
    int status;
    char* address=NULL;
    std::stringstream puerto_str;
    puerto_str << puerto;
    int error=0;
    host_info.ai_family = AF_UNSPEC;
    host_info.ai_socktype = SOCK_STREAM;
    if (direccion!="")
        address= (char*)direccion.c_str();
    else
        host_info.ai_flags = AI_PASSIVE;

    status = getaddrinfo(address, puerto_str.str().c_str(),\
                         &host_info, &host_info_list);

    if (status != 0) {
        DEBUG_MSG("Error en getaddrinfo.");
        error= 1;
    }
return error;
}

int Socket::getSocketDescriptor(){
        int socketd=0;
        if (host_info_list!=NULL){ // Si fueron seteados las estructuras
            socketd = socket(host_info_list->ai_family,   \
                                           host_info_list->ai_socktype, \
                                           host_info_list->ai_protocol);
            if (socketd == -1){
                DEBUG_MSG("Error en socket.");
                return -1;
            }
        }
return socketd;
}

int Socket::enviar(char* mensaje, uint32_t tamanio){
    int error=-1;
    if (estaConectado()){
        DEBUG_MSG("Enviando mensaje...");
        ssize_t bytes_enviados;
        char paquete[TAMANIO_PAQUETE]={0};
        memcpy(paquete,mensaje,tamanio);

        bytes_enviados = send(this->getSocket(), paquete, TAMANIO_PAQUETE, 0);
        if (bytes_enviados!=-1)
            return error=bytes_enviados;
    }
return error;
}

int Socket::recibir(char** buffer_entrada){
    ssize_t bytes_recibidos;
    int error=-1;
    *buffer_entrada= new char[TAMANIO_PAQUETE];

    bytes_recibidos = recv(this->getSocket(), \
            *buffer_entrada,TAMANIO_PAQUETE, 0);
    if (bytes_recibidos == 0) {
      DEBUG_MSG("Servidor apagado.");
    } else {
      if (bytes_recibidos == -1){
        DEBUG_MSG("Error de recepcion.");
      } else {
        if (bytes_recibidos == TAMANIO_PAQUETE)
            error=TAMANIO_PAQUETE;
      }
    }
    if (error!=TAMANIO_PAQUETE)
        delete[] *buffer_entrada;

return error;
}

void Socket::cerrar(){
	if (MODO_DEBUG==1)
      std::cout << "Cerrando: " << this->aString() << std::endl;
    close(this->socketfd);
    this->socketfd=PUERTO_NO_ABIERTO;
}

bool Socket::estaConectado(){
return this->getSocket()!=PUERTO_NO_ABIERTO;
}

void Socket::apagar(){
	shutdown(this->socketfd,2);
}

std::string Socket::aString(){
    std::stringstream s;
    s << "Puerto: " << getPuerto() << ", Socket: " << getSocket();
return s.str();
}

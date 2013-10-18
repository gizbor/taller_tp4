#include "common_Socket.h"
#include <string>

Socket::Socket(){
    this->socketfd=PUERTO_NO_ABIERTO;
}

Socket::~Socket(){
}

int Socket::enviar(char* mensaje, uint32_t tamanio){
    if (estaConectado()){
        DEBUG_MSG("Enviando mensaje...");
        ssize_t bytes_enviados;
        char paquete[TAMANIO_PAQUETE]={0};
        memcpy(paquete,mensaje,tamanio);

        bytes_enviados = send(this->getSocket(), paquete, TAMANIO_PAQUETE, 0);
        if (bytes_enviados==-1)
            return -1;
    } else {
        return -1;
    }
return 0;
}

int Socket::recibir(char** buffer_entrada){
    ssize_t bytes_recibidos;
    int error;
    *buffer_entrada= new char[TAMANIO_PAQUETE];

    bytes_recibidos = recv(this->getSocket(), \
            *buffer_entrada,TAMANIO_PAQUETE, 0);
    if (bytes_recibidos == 0) {
      DEBUG_MSG("Servidor apagado.");
     error= 0;
    } else {
      if (bytes_recibidos == -1){
        DEBUG_MSG("Error de recepcion.");
        error=-1;
      } else {
        if (bytes_recibidos != TAMANIO_PAQUETE)
            error=-2;
        else
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

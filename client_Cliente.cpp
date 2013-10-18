#include "client_Cliente.h"
#include <string>

Cliente::Cliente(std::string direccion,t_puerto puerto){
    osocket.setDireccion(direccion);
    osocket.setPuerto(puerto);
}

Cliente::~Cliente(){
}

int Cliente::conectar(){
   if (osocket.conectar()!=0)
    return 1;
return 0;
}

void Cliente::desconectar(){
   osocket.cerrar();
}

int Cliente::enviar(const char* msg, uint32_t tamanio){
    int error=0;
    uint32_t tamanio_msg;
    char* serial_msg;
    tamanio_msg= serializarMsg(msg, tamanio, &serial_msg);

    if (!osocket.estaConectado() || \
        this->osocket.enviar(serial_msg, tamanio_msg)!=0){
        DEBUG_MSG("Error enviando.");
        error=1;
    }
    delete[] serial_msg;
return error;
}


int Cliente::recibir(char** mensaje, uint32_t& tamanio){
    char *buffer;
    if (osocket.recibir(&buffer)>0){
        tamanio=deserializarMsg(buffer, mensaje);

        if (MODO_DEBUG==1)
            imprimirMsg(*mensaje,tamanio);
    delete[] buffer;
    } else {
            return 1;
    }
return 0;
}

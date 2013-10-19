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
    tamanio_msg= protocolo.serializarMsg(msg, tamanio, &serial_msg);

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
        tamanio=protocolo.deserializarMsg(buffer, mensaje);

        if (MODO_DEBUG==1)
            protocolo.imprimirMsg(*mensaje,tamanio);
    delete[] buffer;
    } else {
            return 1;
    }
return 0;
}

int Cliente::transmitirArchivo(std::ifstream& archivo){
      uint32_t  tamanio_recv;
      char *mensaje_recibido, c;
      std::string mensaje_envio;
      int error=1;

      if (this->conectar()==0){
          /* Recibir bienvenida */
          if (this->recibir(&mensaje_recibido,tamanio_recv)==0){
            std::cout << "[SERVIDOR] ";
            Protocolo::imprimirMsg(mensaje_recibido,tamanio_recv);
            delete[] mensaje_recibido;
            /* Enviar mensaje */
            std::cout << "[CLIENTE] Enviando datos..." << std::endl;
            while(!archivo.eof() && archivo.get(c))
                 mensaje_envio.push_back(c);

            if (this->enviar(mensaje_envio.c_str(),mensaje_envio.length())==0){
                  /* Recibir mensaje de recepcion del servidor */
                  if (this->recibir(&mensaje_recibido,tamanio_recv)==0){
                    if (protocolo.validarMensajeRecepcion(mensaje_recibido, tamanio_recv, (uint32_t)mensaje_envio.length())==0){
                       std::cout << "[SERVIDOR] ";
                       Protocolo::imprimirMsg(mensaje_recibido,tamanio_recv);
                       error=0;
                    }
                  delete[] mensaje_recibido;
                  }
            }
          }
          this->desconectar();
      }
return error;
}

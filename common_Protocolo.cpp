#include "common_Protocolo.h"

Protocolo::Protocolo() {
    //ctor
}

Protocolo::~Protocolo() {
    //dtor
}

void Protocolo::msgAString(const char* des_msg, uint32_t tamanio, std::string& des_str) {
    des_str.assign(des_msg, (size_t)tamanio);
    des_str.append(1,'\0');
}

void Protocolo::imprimirMsg(const char* des_msg, uint32_t tamanio) {
    std::cout.write(des_msg, tamanio);
    std::cout << std::endl;
}

uint32_t Protocolo::serializarMsg(const char* msg, uint32_t tamanio, char** serial_msg) {
    uint32_t long_msg=htonl(tamanio);
    uint32_t long_total=tamanio+sizeof(uint32_t);
    *serial_msg= new char[long_total];
    memcpy(*serial_msg, &long_msg, sizeof(uint32_t));
    memcpy(*serial_msg+sizeof(uint32_t), msg, tamanio);
    return long_total;
}

uint32_t Protocolo::deserializarMsg(const char* serial_msg, char** des_msg) {
    uint32_t long_msg;
    memcpy(&long_msg, serial_msg,sizeof(uint32_t));
    long_msg=ntohl(long_msg);
    *des_msg=new char[long_msg];
    memcpy(*des_msg,serial_msg+sizeof(uint32_t),long_msg);
    return long_msg;
}

int Protocolo::validarMensajeRecepcion(const char* mensaje_recibido, \
                                                    uint32_t tamanio_recv, uint32_t tamanio_envio){
  std::stringstream s_esperado;
  std::string s_recibido;
  s_esperado <<  "Datos recibidos exitosamente. Cantidad de bytes recibidos: "
   << tamanio_envio << ".";
  msgAString(mensaje_recibido, tamanio_recv, s_recibido);
  if (strcmp(s_esperado.str().c_str(),s_recibido.c_str())!=0)
     return 1;
return 0;
}

#include "common_General.h"
#include <string>

/** Descripcion: envia mensaje al servidor con el siguiente formato,
      long.del msg(t_prefijo)|mensaje(ascii)
*/
uint32_t getTamanio(std::ifstream& archivo){
    archivo.seekg(0, archivo.end);
    uint32_t n=(uint32_t)archivo.tellg();//  getTamanio(archivo);
    archivo.seekg(0, archivo.beg);
return (uint32_t)n;
}

/** Descripcion: extrae el  mensaje de la cadena pasada por parametro.
*     PRE: formato de cadena pasada por parametro cumple con el formato
*     especificado por el protocolo,
*    (longitud:uint32_t en Big Endian)(mensaje:cadena ascii)
*    POS: se retorna mediante des_msg la posicion dentro de serial_msg
*    donde comienza el mensaje.
*    Retorno: longitud del mensaje.
*                   "mensaje" apunta al string terminado en '\0'
*/
uint32_t deserializarMsg(const char* serial_msg, char** des_msg){
    uint32_t long_msg;
    memcpy(&long_msg, serial_msg,sizeof(uint32_t));
    long_msg=ntohl(long_msg);
    *des_msg=new char[long_msg];
    memcpy(*des_msg,serial_msg+sizeof(uint32_t),long_msg);
return long_msg;
}

/** Descripcion: genera mensaje con el formato especificado por el protocolo,
*    (longitud:uint32_t en Big Endian)(mensaje:cadena ascii)
*    POS: el mensaje original no se modifica.
*    Retorno: puntero a mensaje serializado.
*/
 uint32_t serializarMsg(const char* msg, uint32_t tamanio, char** serial_msg){
    uint32_t long_msg=htonl(tamanio);
    uint32_t long_total=tamanio+sizeof(uint32_t);
    *serial_msg= new char[long_total];
    memcpy(*serial_msg, &long_msg, sizeof(uint32_t));
    memcpy(*serial_msg+sizeof(uint32_t), msg, tamanio);
return long_total;
}

void imprimirMsg(const char* des_msg, uint32_t tamanio){
    std::cout.write(des_msg, tamanio);
    std::cout << std::endl;
}

void msgAString(const char* des_msg, uint32_t tamanio, std::string& des_str){
    des_str.assign(des_msg, (size_t)tamanio);
    des_str.append(1,'\0');
}

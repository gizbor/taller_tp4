#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include "common_General.h"
#include <string>

uint32_t getTamanio(std::ifstream& archivo);

/** Descripcion: extrae el  mensaje de la cadena pasada por parametro.
*     PRE: formato de cadena pasada por parametro cumple con el formato
*     especificado por el protocolo,
*    (longitud:uint32_t en Big Endian)(mensaje:cadena ascii)
*    POS: se retorna mediante des_msg la posicion dentro de serial_msg
*    donde comienza el mensaje.
*    Retorno: longitud del mensaje.
*                   "mensaje" apunta al string terminado en '\0'
*/
uint32_t deserializarMsg(const char* serial_msg, char** des_msg);
/** Descripcion: genera mensaje con el formato especificado por el protocolo,
*    (longitud:uint32_t en Big Endian)(mensaje:cadena ascii)
*    POS: el mensaje original no se modifica.
*    Retorno: puntero a mensaje serializado.
*/
uint32_t serializarMsg(const char* msg, uint32_t tamanio, char** serial_msg);

void imprimirMsg(const char* des_msg, uint32_t tamanio);

void msgAString(const char* des_msg, uint32_t tamanio, std::string& mensaje);
#endif // FUNCIONES_H_INCLUDED

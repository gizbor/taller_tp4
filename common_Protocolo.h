#ifndef PROTOCOLO_H
#define PROTOCOLO_H
#include "common_General.h"
#include <string>

class Protocolo{
    public:
     Protocolo() {}
     virtual ~Protocolo() {}
     /** Descripcion: extrae el  mensaje de la cadena pasada por parametro.
     *     PRE: formato de cadena pasada por parametro cumple con el formato
     *     especificado por el protocolo,
     *    (longitud:uint32_t en Big Endian)(mensaje:cadena ascii)
     *    POS: se retorna mediante des_msg la posicion dentro de serial_msg
     *    donde comienza el mensaje.
     *    Retorno: longitud del mensaje.
     *                   "mensaje" apunta al string terminado en '\0'
     */
      static uint32_t deserializarMsg(const char* serial_msg, char** des_msg);
     /** Descripcion: genera mensaje con el formato especificado por el
     *     protocolo,
     *    (longitud:uint32_t en Big Endian)(mensaje:cadena ascii)
     *    POS: el mensaje original no se modifica.
     *    Retorno: puntero a mensaje serializado.
     */
      static uint32_t serializarMsg(const char* msg, uint32_t tamanio, \
                                                         char** serial_msg);
     /** Descripcion: imprime por pantalla el mensaje deserializado "des_msg"
     *   de tamanio "tamanio".
     *    Retorno: -
     */
      static void imprimirMsg(const char* des_msg, uint32_t tamanio);

     /** Descripcion: convierte a string el mensaje deserializado "des_msg" de 
     *   tamanio "tamanio" y lo copia en el parametro "mensaje".
     *   Retorno: -
     */
      static void msgAString(const char* des_msg, \
                             uint32_t tamanio, std::string& mensaje);
     /** Descripcion: valida si el mensaje de confirmacion de recepcion 
     *   enviado es correcto.
     *   Retorno: 0 -> es valido, 1 -> es invalido
     */
      int validarMensajeRecepcion(const char* mensaje_recibido, \
                         uint32_t tamanio_recv, uint32_t tamanio_envio);  
};

#endif // PROTOCOLO_H

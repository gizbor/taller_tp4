#include "client_Cliente.h"
#include "common_funciones.h"
#include <fstream>
#include <string>
#define TAMANIO_MAX_MSG 3000

int validarMensajeRecepcion(const char* mensaje_recibido, \
                                uint32_t tamanio_recv, uint32_t tamanio_envio);
void parsearDatos(char const * dir_puerto, std::string& direccion,\
                                t_puerto& puerto);
int procesar(std::string direccion, t_puerto puerto, std::string mensaje_envio);



int main(int argc, char** argv){
  std::string direccion;
  t_puerto puerto;
  std::ifstream archivo;
  int error=0;
  std::string mensaje_envio;
  char c;

  if (argc >= 2){
      if (argc == 3){
          archivo.open(argv[2]);
          while(!archivo.eof() && archivo.get(c)){
            mensaje_envio.push_back(c);
          }
          archivo.close();
      } else {
          while(!std::cin.eof() && std::cin.get(c)){
            mensaje_envio.push_back(c);
          }
      }
      parsearDatos(argv[1],direccion,puerto);

      /** Proceso principal cliente **/
      error=procesar(direccion,puerto,mensaje_envio);
    } else {
      error=-1;
    }
return error;
}


int validarMensajeRecepcion(const char* mensaje_recibido, \
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

void parsearDatos(char const * dir_puerto, std::string& direccion,\
                          t_puerto& puerto){
    std::stringstream puerto_str;
    char c;
    while ((c=*(dir_puerto++)) && c!=':')
       direccion.push_back(c);
    while ((c=*(dir_puerto++)) && c!='\0')
       puerto_str << c;
       puerto_str >> puerto;
}

int procesar(std::string direccion, t_puerto puerto, std::string mensaje_envio){
      uint32_t tamanio_envio, tamanio_recv;
      char *mensaje_recibido;
      int error=0;

      tamanio_envio=mensaje_envio.length();

      Cliente c(direccion, puerto);
      if (c.conectar()!=0){
          error=1;
      } else {
          /* Recibir bienvenida */
          if (c.recibir(&mensaje_recibido,tamanio_recv)!=0){
            error=2;
          } else {
            std::cout << "[SERVIDOR] ";
            imprimirMsg(mensaje_recibido,tamanio_recv);
            delete[] mensaje_recibido;
            /* Enviar mensaje */
            std::cout << "[CLIENTE] Enviando datos..." << std::endl;
            if (c.enviar(mensaje_envio.c_str(),tamanio_envio)!=0){
              error=3;
            } else { /* Recibir mensaje de recepcion del servidor */
                  if (c.recibir(&mensaje_recibido,tamanio_recv)!=0){
                    error=3;
                  } else {
                    if (validarMensajeRecepcion(mensaje_recibido,tamanio_recv,\
                                                  tamanio_envio)!=0){
                       error=3;
                    } else {
                       std::cout << "[SERVIDOR] ";
                       imprimirMsg(mensaje_recibido,tamanio_recv);
                    }
                  delete[] mensaje_recibido;
                  }
            }
          }
      }
return error;
}


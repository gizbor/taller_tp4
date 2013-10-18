#include "client_Cliente.h"
#include "common_funciones.h"
#include <fstream>
#include <string>

#define TAMANIO_MAX_MSG 3000

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

int main(int argc, char** argv){
  uint32_t tamanio_envio, tamanio_recv;
//  char mensaje_envio[TAMANIO_MAX_MSG]={0};
  char *mensaje_recibido;
  std::string direccion;
  t_puerto puerto;
  std::ifstream archivo;
  int error=0;

//  argv[2]="../Pruebas/326/client1.in"; // Prueba 1
////  argv[1]="127.0.0.1:9001";
////  argv[2]="< ../Pruebas/326/client1.in"
//  argc=2;

//  argv[2]="../Pruebas/330/client1.in"; // Prueba 2
//  argv[1]="127.0.0.1:9001"; // 9000 no abre
//  argc=3;

//  argv[2]="../Pruebas/327/client1.in"; argv[1]="127.0.0.1:9001";// Prueba 2 C1
//  argv[2]="../Pruebas/327/client2.in"; argv[1]="127.0.0.1:9002"; // Prueba 2 C2
//  argc=3;
//std::cout << argc;
  std::string mensaje_envio;
  char c;
  if (argc >= 2){
      if (argc == 3){
          archivo.open(argv[2]);
          while(!archivo.eof() && archivo.get(c)){
            mensaje_envio.push_back(c);
          }
//          tamanio_envio=getTamanio(archivo);
//          archivo.read(mensaje_envio,tamanio_envio);
          archivo.close();
      } else {
          while(!std::cin.eof() && std::cin.get(c)){
            mensaje_envio.push_back(c);
          }
      }
      tamanio_envio=mensaje_envio.length();
//      std::cout << "A: " <<mensaje_envio << " " << tamanio_envio <<std::endl;
//        return -4;
      parsearDatos(argv[1],direccion,puerto);
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
            if (c.enviar(mensaje_envio.c_str(), tamanio_envio)!=0){
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
    } else {
        error=-1; /* Parametros invalidos */
    }
return error;
}

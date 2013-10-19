#include "client_Cliente.h"
#include "common_funciones.h"
#include "common_Protocolo.h"
#include <fstream>
#include <string>

void parsearParametros(char const * dir_puerto, std::string& direccion,\
                                t_puerto& puerto);

int main(int argc, char** argv){
  std::string direccion;
  t_puerto puerto;
  std::ifstream* parchivo;
  int error=-1;

  if (argc >= 2){
      parsearParametros(argv[1],direccion,puerto);
      Cliente cliente(direccion,puerto);

     if (argc == 3){
        parchivo=new std::ifstream();
        parchivo->open(argv[2]);
      } else {
        parchivo=(std::ifstream*)&std::cin;
      }
      error=cliente.transmitirArchivo(*parchivo);
    }
    if (argc==3){
        parchivo->close();
        delete parchivo;
    }
return error;
}


void parsearParametros(char const * dir_puerto, std::string& direccion,\
                          t_puerto& puerto){
    std::stringstream puerto_str;
    char c;
    while ((c=*(dir_puerto++)) && c!=':')
       direccion.push_back(c);
    while ((c=*(dir_puerto++)) && c!='\0')
       puerto_str << c;
       puerto_str >> puerto;
}




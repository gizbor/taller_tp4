#include "client_Cliente.h"
#include "common_Protocolo.h"
#include <fstream>
#include <string>

/************ 75.42 - TALLER DE PROGRAMACION I: Cátedra Veiga **************
*    TRABAJO PRACTICO 4: "Open Port Toolkit"
*    Nro. de entrega/Fecha: 2/20-10-2013 de Septiembre
*    Alumno: Gustavo Martín Borello
*    Padrón: 90670
*    Año/Cuatrimestre: 2013/2
******************************************************************************/

int main(int argc, char** argv){
  std::ifstream* parchivo;
  int error=-1;

  if (argc >= 2){
      Cliente cliente(argv[1]);

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

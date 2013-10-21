#include "server_Servidor.h"
#include <string>
#include "server_ApagaServidor.h"

/************ 75.42 - TALLER DE PROGRAMACION I: Cátedra Veiga **************
*    TRABAJO PRACTICO 4: "Open Port Toolkit"
*    Nro. de entrega/Fecha: 2/20-10-2013 de Septiembre
*    Alumno: Gustavo Martín Borello
*    Padrón: 90670
*    Año/Cuatrimestre: 2013/2
******************************************************************************/

int main(int argc, char** argv){
    int error=-1;
    Servidor servidor;
    ApagaServidor apagador(&servidor);

    servidor.setApagador(&apagador);

    if (argc == 2)
        error=servidor.iniciar(argv[1]);


return error;
}



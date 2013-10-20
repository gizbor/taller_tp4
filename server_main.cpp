#include "server_Servidor.h"
#include <pthread.h>
#include <string>
#include "server_ApagaServidor.h"

int main(int argc, char** argv){
    int error=-1;
    Servidor servidor;
    ApagaServidor apagador(&servidor);

    servidor.setApagador(&apagador);

    if (argc == 2)
        error=servidor.iniciar(argv[1]);


return error;
}



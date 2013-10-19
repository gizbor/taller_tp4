#include "server_Servidor.h"
#include <pthread.h>
#include <string>


int main(int argc, char** argv){
    int error=0;
    Servidor servidor;
    std::string puertos;
    if (argc == 2){
        puertos=argv[1];
        error=servidor.iniciar(argv[1]);
    } else {
        error=-1;
    }

return error;
}



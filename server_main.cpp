#include "server_Servidor.h"
#include <iostream>
#include <vector>
#include <pthread.h>
#include <string>

void parsearPuertos(const char* puertos, std::vector<t_puerto> &vpuertos);
int procesar(std::string puertos);

int main(int argc, char** argv){
    int error=0;
    if (argc == 2)
        error=procesar(argv[1]);
    else
        error=-1;

return error;
}

void parsearPuertos(const char* puertos, std::vector<t_puerto> &vpuertos){
    std::stringstream s;
    t_puerto p;
    char c=*(puertos++);
    while (c!='\n' && c!='\0'){
        while (c!=','  && c!='\n' && c!='\0'){
            s << c;
            c=*(puertos++);
        }
        s >> p;  s.clear();
        if (c==',') c=*(puertos++);
        vpuertos.push_back(p);
    }
}

int procesar(std::string puertos){
        Servidor server;
        std::vector<int> threads;

        int error= 0;

        pthread_t hilo;
        std::vector<t_puerto> vpuertos;
        parsearPuertos(puertos.c_str(), vpuertos);

        std::vector<t_puerto>::iterator itp;
        itp = vpuertos.begin();

        /* Intento abrir puertos */
        while (itp != vpuertos.end()) {
            if (server.abrir(*itp)!=0)
                if (!server.estaAbierto(*itp))
                    error++;
        itp++;
        }
        /* Escucha puertos que pudieton abrirse */
        if (error < (int)vpuertos.size()){
            for (itp=vpuertos.begin(); itp!=vpuertos.end(); ++itp){
                    if (server.estaAbierto(*itp)){
                        hilo=server.escuchar(*itp);
                        threads.push_back(hilo);
                    }
            }
            /* Espera caracter 'q' para salir */
            hilo=server.apagador();
            threads.push_back(hilo);

            for (int i_thread=0; i_thread<(int)threads.size(); i_thread++){
                pthread_join(threads[i_thread],NULL);
            }
        }
        server.cerrar();
return error;
}

#include "server_Servidor.h"
#include <string>
#include <vector>

Servidor::Servidor(){
}

Servidor::~Servidor(){
    for (unsigned int i=0; i<puertos.size(); i++)
        delete puertos[i];
}

pthread_mutex_t Servidor::log_mutex = PTHREAD_MUTEX_INITIALIZER;

int Servidor::abrir(t_puerto puerto){
    std::stringstream mensaje;

    ServerSocket* socket=new ServerSocket();
    socket->setPuerto(puerto);
    if (socket->conectar()==0){
        puertos.push_back(socket);
        mensaje << "PUERTO " << puerto << ". Abierto.";
        Servidor::loguear(mensaje.str());
    } else {
        delete socket;
        mensaje.str("");
        mensaje << "PUERTO " << puerto << ". Error.";
        Servidor::loguear(mensaje.str());
        return 1;
    }
return 0;
}

bool Servidor::estaAbierto(t_puerto puerto){
return this->getSocket(puerto)!=NULL;
}

pthread_t Servidor::escuchar(t_puerto puerto){
    pthread_t hilo;
    ServerSocket* socket=getSocket(puerto);
    pthread_create(&hilo, NULL, &Servidor::aceptar, \
                    reinterpret_cast<void*>(socket));
return hilo;
}

ServerSocket* Servidor::getSocket(t_puerto puerto){
    ServerSocket* s=NULL;
    for (unsigned int i=0; i<puertos.size(); i++){
        if (puertos[i]->getPuerto()==puerto){
            s=puertos[i];
            break;
        }
    }
return s;
}

void Servidor::cerrar(){
    DEBUG_MSG("Cerrando puertos del servidor.");
    for (unsigned int i=0; i<puertos.size(); i++)
        puertos[i]->cerrar();
}

int Servidor::confirmarConexion(ServerSocket& socket){
      std::stringstream mensaje_confirmacion;
      int error=-1;
      uint32_t tamanio_confirmacion;
      char *confirmacion_serial=NULL;
      mensaje_confirmacion.str("");
      mensaje_confirmacion << "PUERTO " << socket.getPuerto() \
                           << " Aceptado. Recibiendo datos...";
      tamanio_confirmacion=protocolo.serializarMsg(mensaje_confirmacion.str().c_str(),\
                   mensaje_confirmacion.str().length(),&confirmacion_serial);
      error=socket.enviar(confirmacion_serial,tamanio_confirmacion);
      delete[] confirmacion_serial;
return error;
}

// -1: error, bytes recibidos
int Servidor::recibirArchivo(ServerSocket& socket, char** buffer_entrada){
    int tamanio=-1;
    char *mensaje_cliente=NULL;
    std::string mensaje;
              if (socket.recibir(buffer_entrada)<=0){
                    DEBUG_MSG("Error recibiendo archivo del cliente.");
              } else {
               tamanio= protocolo.deserializarMsg(*buffer_entrada, &mensaje_cliente);
               if (MODO_DEBUG==1){
                   msgAString(mensaje_cliente,tamanio,mensaje);
                   Servidor::loguear(mensaje);
               }
               delete[] mensaje_cliente;
              }
return tamanio;
}
int Servidor::enviarConfirmacionArchivo(ServerSocket& socket, uint32_t tamanio){
   std::stringstream mensaje_confirmacion;
   char *confirmacion_serial=NULL;
   uint32_t tamanio_confirmacion;
   int error=-1;
   mensaje_confirmacion.str("");
   mensaje_confirmacion \
      << "Datos recibidos exitosamente. Cantidad de bytes recibidos: " \
      << tamanio << ".";
     tamanio_confirmacion=protocolo.serializarMsg(\
                                            mensaje_confirmacion.str().c_str(), \
                                            mensaje_confirmacion.str().length(),\
                                            &confirmacion_serial);
     error=socket.enviar(confirmacion_serial,tamanio_confirmacion);
     delete[] confirmacion_serial;
return error;
}
/* PRE: puerto abierto */
void* Servidor::aceptar(void* po_socket){
 std::stringstream mensaje_log;
 ServerSocket* posocket=reinterpret_cast<ServerSocket*>(po_socket);
 char *buffer_entrada=NULL;
 bool shutdown=false;
 uint32_t tamanio;
 std::string mensaje;

 while (!shutdown){
      if (posocket->aceptar()==0){
          mensaje_log.str("");
          mensaje_log << "PUERTO " << posocket->getPuerto() << \
                       ". Conexión aceptada.";
          Servidor::loguear(mensaje_log.str());
          if (Servidor::confirmarConexion(*posocket)!=0){
            if ((tamanio=Servidor::recibirArchivo(*posocket, &buffer_entrada))!=-1){
                   mensaje_log.str("");
                   mensaje_log << "PUERTO "    << posocket->getPuerto() \
                                       << ". Recibidos " << tamanio << " bytes.";
                   Servidor::loguear(mensaje_log.str());
                   Servidor::enviarConfirmacionArchivo(*posocket, tamanio);
                   delete[] buffer_entrada;
            }
             mensaje_log.str("");
             mensaje_log << "PUERTO " << posocket->getPuerto() << ". Conexión cerrada.";
             Servidor::loguear(mensaje_log.str());
          }
        posocket->cancelar();
       } else {
           shutdown = true;
       }
  }
pthread_exit(NULL);
}

void Servidor::loguear(const std::string& mensaje){
 pthread_mutex_lock(&(Servidor::log_mutex));
 std::cout <<  mensaje << std::endl;
 pthread_mutex_unlock(&(Servidor::log_mutex));
}

/** Descripcion: lanza un thread que escucha la tecla 'q'. Al
    ser presionada procede a ejecutar shutdown de todos los puertos */
pthread_t Servidor::apagador(){
  pthread_t hilo;
  pthread_create(&hilo,NULL,&Servidor::salir,&puertos);
return hilo;
}

void* Servidor::salir(void* p_puertos){
  std::vector<ServerSocket*> &puertos= \
    *static_cast<std::vector<ServerSocket*> *> (p_puertos);
  DEBUG_MSG("Presione 'q' para salir...");
  char c;
  while (std::cin >> c && c!='q'){}
  Servidor::apagar(puertos);
  pthread_exit(NULL);
}

void Servidor::apagar(std::vector<ServerSocket*> &puertos){
  DEBUG_MSG("Apagando servidor\n");
  for (unsigned int i=0; i<puertos.size(); i++)
      puertos[i]->apagar();
}


void Servidor::parsearPuertos(const char* puertos, std::vector<t_puerto> &vpuertos){
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

int Servidor::iniciar(std::string puertos){
        std::vector<int> threads;
        int error= 0;
        pthread_t hilo;
        std::vector<t_puerto> vpuertos;
        parsearPuertos(puertos.c_str(), vpuertos);

        std::vector<t_puerto>::iterator itp;
        itp = vpuertos.begin();

        /* Intento abrir puertos */
        while (itp != vpuertos.end()) {
            if (this->abrir(*itp)!=0)
                if (!this->estaAbierto(*itp))
                    error++;
        itp++;
        }
        /* Escucha puertos que pudieton abrirse */
        if (error < (int)vpuertos.size()){
            for (itp=vpuertos.begin(); itp!=vpuertos.end(); ++itp){
                    if (this->estaAbierto(*itp)){
                        hilo=this->escuchar(*itp);
                        threads.push_back(hilo);
                    }
            }
            /* Espera caracter 'q' para salir */
            hilo=this->apagador();
            threads.push_back(hilo);

            for (int i_thread=0; i_thread<(int)threads.size(); i_thread++){
                pthread_join(threads[i_thread],NULL);
            }
        }
        this->cerrar();
return error;
}




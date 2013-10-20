#include "server_Servidor.h"
#include <string>
#include <vector>

Servidor::Servidor(){
   apagador=NULL;
}

Servidor::~Servidor(){
    for (unsigned int i=0; i<puertos.size(); i++)
        delete puertos[i];
}

pthread_mutex_t Servidor::log_mutex = PTHREAD_MUTEX_INITIALIZER;

int Servidor::abrir(t_puerto puerto){
    std::stringstream mensaje;

    ServerSocket* socket=new ServerSocket(this);
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
                   protocolo.msgAString(mensaje_cliente,tamanio,mensaje);
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
int Servidor::atender(Socket& socketp){
 std::stringstream mensaje_log;
ServerSocket& socket=*((ServerSocket*)&socketp);
 char *buffer_entrada=NULL;
 int error=1;
 uint32_t tamanio;
 std::string mensaje;

          mensaje_log.str("");
          mensaje_log << "PUERTO " << socket.getPuerto() << \
                       ". Conexión aceptada.";
          this->loguear(mensaje_log.str());
          if (this->confirmarConexion(socket)!=0){
            if ((tamanio=this->recibirArchivo(socket, &buffer_entrada))!=-1){
                   mensaje_log.str("");
                   mensaje_log << "PUERTO "    << socket.getPuerto() \
                                       << ". Recibidos " << tamanio << " bytes.";
                   this->loguear(mensaje_log.str());
                   this->enviarConfirmacionArchivo(socket, tamanio);
                   delete[] buffer_entrada;
                   error=0;
            }
             mensaje_log.str("");
             mensaje_log << "PUERTO " << socket.getPuerto() << ". Conexión cerrada.";
             this->loguear(mensaje_log.str());
          }
return error;
}

void Servidor::loguear(const std::string& mensaje){
 pthread_mutex_lock(&(Servidor::log_mutex));
 std::cout <<  mensaje << std::endl;
 pthread_mutex_unlock(&(Servidor::log_mutex));
}

void Servidor::apagar(){
  DEBUG_MSG("Apagando servidor\n");
  for (unsigned int i=0; i<puertos.size(); i++){
      puertos[i]->apagar();
      if (puertos[i]->isFinished())
        puertos[i]->exit();
  }
    ((Thread*)apagador)->exit();
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

int Servidor::iniciar(std::string lista_puertos){
        std::vector<Thread*> threads;
        int error= 0;
        std::vector<t_puerto> vpuertos;
        parsearPuertos(lista_puertos.c_str(), vpuertos);
        std::vector<t_puerto>::iterator itp;
        itp = vpuertos.begin();
        std::vector<ServerSocket*>::iterator itPuertos;

        /* Intento abrir puertos */
        while (itp != vpuertos.end()) {
                if (this->abrir(*itp)!=0)
                    if (!this->estaAbierto(*itp))
                        error++;
            itp++;
        }
        /* Escucha puertos que pudieton abrirse */
        if (error < (int)vpuertos.size()){
            threads.push_back((Thread*)apagador);
            ((Thread*)apagador)->start();
            for (itPuertos=puertos.begin();itPuertos!=puertos.end();++itPuertos){
                (*itPuertos)->start();
                threads.push_back((*itPuertos));
            }

            for (int i_thread=0; i_thread<(int)threads.size(); i_thread++){
                threads[i_thread]->join();
            }
        }
return error;
}


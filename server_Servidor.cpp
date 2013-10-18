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

/* PRE: puerto abierto */
void* Servidor::aceptar(void* po_socket){
 std::stringstream mensaje_log, mensaje_confirmacion;
 ServerSocket* posocket=reinterpret_cast<ServerSocket*>(po_socket);
 int bytes_datos_recibidos;
 char *buffer_entrada=NULL, *mensaje_cliente=NULL, *confirmacion_serial=NULL;
 bool shutdown=false;
 uint32_t tamanio, tamanio_confirmacion;
 int error=0;
 std::string mensaje;

 while (!shutdown){
  if (posocket->aceptar()==0){
      mensaje_log.str("");
      mensaje_log << "PUERTO " << posocket->getPuerto() << \
                   ". Conexión aceptada.";
      Servidor::loguear(mensaje_log.str());
      /* Enviar confirmacion al cliente */
      mensaje_confirmacion.str("");
      mensaje_confirmacion << "PUERTO " << posocket->getPuerto() \
                           << " Aceptado. Recibiendo datos...";
      tamanio_confirmacion=serializarMsg(mensaje_confirmacion.str().c_str(),\
                   mensaje_confirmacion.str().length(),&confirmacion_serial);
      posocket->enviar(confirmacion_serial,tamanio_confirmacion);
      delete[] confirmacion_serial;

      if (error!=0 ||
           (bytes_datos_recibidos=posocket->recibir(&buffer_entrada))<=0){
       DEBUG_MSG("Error recibiendo mensaje del cliente.");
      } else {
       tamanio= deserializarMsg(buffer_entrada, &mensaje_cliente);
       if (MODO_DEBUG==1){
           msgAString(mensaje_cliente,tamanio,mensaje);
           Servidor::loguear(mensaje);
       }
       delete[] mensaje_cliente;
       mensaje_log.str("");
       mensaje_log << "PUERTO " << posocket->getPuerto() << ". Recibidos "\
                   << tamanio << " bytes.";
       Servidor::loguear(mensaje_log.str());
       /* Envia confirmacion... */
       mensaje_confirmacion.str("");
       mensaje_confirmacion \
       << "Datos recibidos exitosamente. Cantidad de bytes recibidos: " \
       << tamanio << ".";
       tamanio_confirmacion=serializarMsg(mensaje_confirmacion.str().c_str(), \
                                          mensaje_confirmacion.str().length(),\
                                          &confirmacion_serial);
       posocket->enviar(confirmacion_serial,tamanio_confirmacion);
       delete[] confirmacion_serial;
       delete[] buffer_entrada;
      }
    mensaje_log.str("");
    mensaje_log << "PUERTO " << posocket->getPuerto() << ". Conexión cerrada.";
    Servidor::loguear(mensaje_log.str());
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





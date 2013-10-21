#ifndef GENERAL_H_INCLUDED
#define GENERAL_H_INCLUDED
#include <stdint.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <cstring>
#include <sys/socket.h>
#include <netdb.h>
typedef unsigned int t_puerto;

#define TAMANIO_PAQUETE 3072

/* Comentar siguiente linea para no mostrar mensajes de debug */
//#define __DEBUG__
#ifdef __DEBUG__
#define DEBUG_MSG(mensaje) printf("[DEBUG] %s\n", mensaje)
#define MODO_DEBUG 0
#else
#define DEBUG_MSG(mensaje) printf("%s", "")
#define MODO_DEBUG 0
#endif

#define PUERTO_NO_ABIERTO -1
#define SOCKET_NO_ABIERTO -1
#define MENSAJE_CONFIRMACION 'OK'



#endif // GENERAL_H_INCLUDED


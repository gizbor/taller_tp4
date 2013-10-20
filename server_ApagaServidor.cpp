#include "server_ApagaServidor.h"

ApagaServidor::ApagaServidor(Servidor* servidor)
{
    setServidor(servidor);
}

ApagaServidor::~ApagaServidor(){
}

void* ApagaServidor::run(){
      DEBUG_MSG("Presione 'q' para salir...");
      char c;
      while (std::cin >> c && c!='q'){}
      this->servidor->apagar();
return (void*)(0);
}


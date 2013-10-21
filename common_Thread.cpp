#include "common_Thread.h"

Thread::Thread(){
    tid=0;
    setStatus(THREAD_NO_INICIADO);
}

Thread::~Thread(){
    if (isRunning())
        this->exit();
}

int Thread::detach(){
   return pthread_detach(this->tid);
}

int Thread::join(){
    int result = -1;
    if (isRunning())
        result = pthread_join(this->tid,NULL);
return result;
}

void Thread::kill(){
    this->setStatus(THREAD_FINALIZADO);
}

bool Thread::isFinished(){
    return this->status==THREAD_FINALIZADO;
}

int Thread::start(){
    int result=1;
    if (!isRunning()){
        result = pthread_create(&tid, NULL, runThread, this);
        if (result == 0)
                this->setStatus(THREAD_CORRIENDO);
    }
return result;
}

bool Thread::isRunning(){
 return (this->status==THREAD_CORRIENDO);
}

void* Thread::runThread(void* arg){
    return ((Thread*)arg)->run();
}

void Thread::exit(){
    if (this->status!=THREAD_NO_INICIADO)
        detach();
    if (isRunning()){
        this->setStatus(THREAD_FINALIZADO);
        pthread_exit(NULL);
    }
}




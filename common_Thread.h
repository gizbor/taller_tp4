#ifndef THREAD_H
#define THREAD_H
#include <pthread.h>
#define THREAD_FINALIZADO 2
#define THREAD_CORRIENDO 1
#define THREAD_NO_INICIADO 0

class Thread
{
    public:
        Thread();
        virtual ~Thread();
        int start();
        int join();
        int detach();
        void exit();
        bool isRunning();
        bool isFinished();
        void kill();
        void setStatus(int status) { this->status=status; }
        virtual void* run() = 0;
        static void* runThread(void* arg);

    protected:
    private:
       pthread_t tid;
       int status;
};

#endif // THREAD_H




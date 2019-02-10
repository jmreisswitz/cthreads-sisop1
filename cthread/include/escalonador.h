#ifndef __escalonador__
#define __escalonador__

//#include "cdata.h"
#include "filas.h"


/// inicializa algumas variáveis necessárias 
void escalonadorInit();

/// faz o dispatch de threads. Retorna -1 caso de erro.
int dispatcher();

/// função que executa uma thread
void* execThread(void *(*func)(void*),void *arg);


int getIniciado();

void setThreademExec(TCB_t* t);

TCB_t* getThreadEmExec();


#endif

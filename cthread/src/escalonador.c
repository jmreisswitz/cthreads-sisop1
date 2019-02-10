#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include "escalonador.h"
#include "cdata.h"
//#include "tcb.h"
//#include "filas.h"


int escalonador_iniciado = 0;
TCB_t*  threadEmExec; // thread que esta rodando
//int maintcb = 0;


void escalonadorInit(){
    
    if(filasInit()!=0)
        printf("Erro criando as filas!\n");

    startTimer();
	threadEmExec = NULL;
    escalonador_iniciado = 1;
}

/*realiza a troca de contexto*/
int dispatcher(){

	if (!aptosVazia()){

        TCB_t* anterior = threadEmExec;
        TCB_t* proxima = (TCB_t*)popAptos();
        startTimer();
        threadEmExec = proxima;
        threadEmExec->state = PROCST_EXEC;
        
        return swapcontext(&anterior->context, &threadEmExec->context);  /// retorna -1 se erro, e não retorna caso contrário
	}
    return -1;
}


void* execThread(void *(*func)(void*),void *arg)
{
    func(arg);

    int tidEsperando = isThreadWaitingFor(threadEmExec->tid);
    
    if(tidEsperando != -1)
    {
        BloqsToAptos(tidEsperando);
    }

    // seta termino
    // coloca na fila de terminados
    TCB_t* t = getThreadEmExec();
    insereTerminados(t);
    deletaTcb(t->tid); //deleta da lista de ativos

    dispatcher();

    return NULL;

}



/*  
    ========== getters and setters =========
*/

TCB_t* getThreadEmExec()
{
    return threadEmExec;
}

int getIniciado(){
    return escalonador_iniciado;
}

void setThreademExec(TCB_t* t)
{
    threadEmExec = t;
}

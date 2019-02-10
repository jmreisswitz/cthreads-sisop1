#include "../include/support.h"
#include "../include/cthread.h"
#include "../include/cdata.h"
#include "../include/escalonador.h"
#include <stdio.h>
#include <stdlib.h>

void function1() {
    
	
}

void tcbCorrente(){
	
	TCB_t* tcb = getThreadEmExec();
	printf("id da thread: %d\n",tcb->tid );
	printf("status da thread: %d\n",tcb->state );

	int tid2;

    tid2 = ccreate ((void *)function1, (void*)NULL, 0);
    if (tid2 < 0 )
       printf("Error creating thread for function 2...\n");
    else printf("Function 1 created thread for function 2\n");

    printf("encerrando a função 1....\n");

}

int main(){
	int a;
	a = ccreate((void*)tcbCorrente, (void*)NULL, 0);
	cjoin(1);

	printf("encerrando main com a = %d...\n",a);

}
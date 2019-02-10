#include <stdio.h>
#include <stdlib.h>
#include "../include/filas.h"
#include "../include/cdata.h"
//#include "../include/support.h"
#include "../include/escalonador.h"


void function3();
void function2();
void function1();
void imprime();

    int a, b;

void imprime(){
	TCB_t* texec = getThreadEmExec();
	printf("Em execucao: tid: %d, prio: %u, state: %d\n", texec->tid, texec->prio, texec->state);
	return;
}

void function3() {


    printf("Function 3 \n");
    printf("Function3 cjoin 2 e nao deveria conseguir por 1 estar esperando\n");
    imprime();

    a = cjoin(2);
    printf("cjoin para 2 = %d -> executando 3\n", a);

    b = cjoin(22);
    printf("cjoin para 22 = %d -> executando 3\n", b);

    printf(">>Function 3 finalizando....\n");
}

void function2() {
    int tid3;

    printf("Function 2 \n");

    tid3 = ccreate ((void *)function3, (void*)NULL, 0);
    if (tid3 < 0 )
       printf("Erro criando thread para function 2...\n");
    else printf("Function 2 criou thread para function 3\n");
    imprime();
    
    printf("Função 2 cjoin 3\n");
    cjoin(3);

    imprime();

    printf("Function2 yielding\n");

    cyield();

    imprime();
    
    printf("Function 2 recebe a cpu porque outras threads estao bloqueadas\n");

    printf(">>Function 2 finalizando....\n");
}

void function1() {
    int tid2;
    imprime();

    printf("Function 1 \n");

    tid2 = ccreate ((void *)function2, (void*)NULL, 0);
    if (tid2 < 0 )
       printf("Error criando thread para function 2...\n");
    else printf("Function 1 criou thread para function 2\n");


    printf("Function 1 cjoin para function 2\n");
    cjoin(2);

    imprime();

    printf(">>Function1 finalizando...\n");
}

int main(int argc, char **argv) {
    int tid1, tid3;
    //imprime();

    printf("Main !\n");

    tid1 = ccreate ((void *)function1, (void*)NULL, 0);
    if (tid1 < 0 )
       printf("Error criando thread para function 1...\n");
    else printf("Main criou thread para function 1\n");

    cjoin(1);
    imprime();
    tid3 = ccreate ((void *)function3, (void*)NULL, 0);
    if (tid1 < 0 )
       printf("Erro para criar outra thread de function 3...\n");
    else printf("Main criou outra thread para function 3\n");
    cjoin(4);
    printf("Main joining function 3\n");
    imprime();

    printf(" imprimindo a = %d e b = %d\n", a ,b); // nao pode ser 0 quando uma thread nao existe
    printf(">>Main encerrando...\n");

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include "../include/filas.h"
#include "../include/cdata.h"
//#include "../include/support.h"
#include "../include/escalonador.h"

void imprime(){
	TCB_t* texec = esca_getThreadEmExec();
	printf("Em execucao: tid: %d, prio: %u, state: %d\n", texec->tid, texec->prio, texec->state);
	return;
}

int main()
{
	filas_Init();

	int a;

	TCB_t* tcb1, *tcb2, *tcb3, *tcb4, *tcb5;
	tcb1 = (TCB_t*) malloc(sizeof(TCB_t));
	tcb1->tid = 1;
	tcb1->prio = 1;
	tcb2 = (TCB_t*) malloc(sizeof(TCB_t));
	tcb2->tid = 2;
	tcb2->prio = 2;
	tcb3 = (TCB_t*) malloc(sizeof(TCB_t));
	tcb3->tid = 3;
	tcb3->prio = 3;
	tcb4 = (TCB_t*) malloc(sizeof(TCB_t));
	tcb4->tid = 4;
	tcb4->prio = 4;
	tcb5 = (TCB_t*) malloc(sizeof(TCB_t));
	tcb5->tid = 5;
	tcb5->prio = 5;

	TCB_t* t;

	ccreate((void*)imprime, (void*)NULL, 0);
	cjoin(1);


	filas_printTidsFilas();

	filas_insereAptos(tcb2);
	filas_insereAptos(tcb4);
	filas_insereAptos(tcb1);

	filas_printTidsFilas();

	t = filas_popAptos();
	printf("t = %d\n", t->tid);
	filas_insereAptos(tcb3);
	filas_insereAptos(tcb5);

	filas_printTidsFilas();


	t = filas_popAptos();
	printf("t = %d\n", t->tid);
	
	t = filas_popAptos();
	printf("t = %d\n", t->tid);
	t = filas_popAptos();

	filas_insereBloqs(tcb1);
	filas_insereBloqs(tcb2);
	filas_insereBloqs(tcb3);
	filas_insereBloqs(tcb4);

	filas_printTidsFilas();

	a =filas_existeThread(1);
		printf("se existe eh != -1: %d\n", a);

	a =filas_existeThread(2);
		printf("se existe eh != -1: %d\n", a);

	a =filas_existeThread(3);
		printf("se existe eh != -1: %d\n", a);

	a =filas_existeThread(4);
		printf("se existe eh != -1: %d\n", a);

	a =filas_existeThread(5);
		printf("se existe eh != -1: %d\n", a);

	a =filas_existeThread(6);
		printf("se existe eh != -1: %d\n", a);

	printf("Tamanho das filas = %d\n", filas_tam());

	imprime();

	if(filas_aptosVazia())
		printf("Fila de aptos vazia\n");
	else	
		printf("Fila de aptos tem algo\n");

	filas_popAptos();

	if(filas_aptosVazia())
		printf("Fila de aptos vazia\n");
	else	
		printf("Fila de aptos tem algo\n");

	filas_printTidsFilas();

	printf("Tamanho das filas = %d\n", filas_tam());	

	imprime();

	printf("miau\n");


	return 0;
}
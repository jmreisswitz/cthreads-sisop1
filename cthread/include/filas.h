#ifndef __filas__
#define __filas__

#include "support.h"
#include "tcb.h"
#include "cthread.h"
#include "escalonador.h"
//#include "tcb.h"


/*
	Retorna == 0 caso sucesso
	retorna != caso não;
*/
int filasInit();


void insereTcb(int tid);
int deletaTcb(int tid);
int setThreadWaiting(int tid, int wait);
int isThreadWaitingFor(int tid);

int BloqsToAptos(int tid);


int insereTerminados(TCB_t* t);


/*
	Insere ordenado pelo Tid nas filas. 
	Retorna  == 0 caso conseguiu
			 != 0 caso não consiga
*/
int insereAptos(TCB_t* thread);
int insereBloqs(TCB_t *thread);


/*
	retorna 1 caso a fila esteja vazia, 0 c.c.
*/
int aptosVazia();

/*
	Retorna o primeiro elemento da fila, REMOVENDO-O dela. 
	Retorna NULL em caso de erro.
*/
TCB_t* popAptos();
TCB_t* popBloqs();

/*
	retorna 0 caso sucesso, != 0 c.c.
*/
int removeBloqs(int tid);


/*
	retorna a soma do tamanho das 2 filas
*/
int tam();


// printa os Tids dos elementos da fila. Usado para debug
void printTidsFilas();

/*
	busca em uma fila - retorna o tid da thread caso ela exista, ou -1 c.c.
*/
int buscaEmFila(int tid, PFILA2 fila);

/*
	busca em aptos e bloqueados: retorna o tid da thread caso ela exista, ou -1 c.c.
*/
int existeThread(int tid);



#endif
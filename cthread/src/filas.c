

/********************************************************************
	Vers. 17.2 - 11/09/2017
********************************************************************/

#include <stdio.h>
#include <stdlib.h>
//#include "support.h"
#include "filas.h"
#include "cthread.h"
#include "escalonador.h"
//#include "cthread.h"

typedef struct fTcbs{
	int tid;
	int wait; // wait = -1 que ngm está esperando. Caso wait > 0 a thread id == wait está esperando pelo fim desta
} simpTcb;


PFILA2 filaAptos;	
PFILA2 filaBloqs;
PFILA2 listaTcbs;
PFILA2 listaTerminados;

/*inicializa fila*/
int filasInit()
{
	listaTcbs = (PFILA2)malloc(sizeof(FILA2));
	filaAptos = (PFILA2)malloc(sizeof(FILA2));
	filaBloqs = (PFILA2)malloc(sizeof(FILA2));
	listaTerminados = (PFILA2)malloc(sizeof(FILA2));
	if(listaTcbs == NULL || filaAptos == NULL || filaBloqs == NULL || listaTerminados == NULL)
		return -1;
	else
		return 0;
}

/*insere na fila de controle de threads*/
void insereTcb(int tid){
	simpTcb* t = (simpTcb*)malloc(sizeof(simpTcb));
	t->tid = tid;
	t->wait = -1;
	AppendFila2(listaTcbs, (void *)t);
}



/* remove thread terminada
retorna 0 caso sucesso, != 0 c.c.*/
int deletaTcb(int tid){
	simpTcb* it;
	if(FirstFila2(listaTcbs) == 0)
	{
		do
		{
			it = (simpTcb*)GetAtIteratorFila2(listaTcbs);
			if(it->tid == tid){
				//it->state = PROCST_TERMINO;
				//AppendFila2(listaTerminados, it); 
				DeleteAtIteratorFila2(listaTcbs);
				return 0;
			}	
		}
		while(NextFila2(listaTcbs)==0);
		return -1;
	}
	return -1;
}



/*atualiza thread que é aguarda por outra, indicando qual a thred que aguarda - cjoin
retorna 0 se conseguiu, -1 se não
*/
int setThreadWaiting(int tid, int wait) 
{	
	simpTcb* it;
	if(FirstFila2(listaTcbs) == 0)
	{
		do
		{
			it = (simpTcb*)GetAtIteratorFila2(listaTcbs);
			if(it->tid == tid){
				DeleteAtIteratorFila2(listaTcbs);
				it->wait = wait;
				AppendFila2(listaTcbs, it);
				return 0;
			}	
		}
		while(NextFila2(listaTcbs)==0);
		return -1;
	}
	return -1;
}


/*busca se termino de thread está sendo aguardado para liberar outra - cjoin
retorna tid para sucesso, -1 caso contrário
*/
int isThreadWaitingFor(int tid)
{
	simpTcb* it;
	if(FirstFila2(listaTcbs) == 0)
	{
		do
		{
			it = (simpTcb*)GetAtIteratorFila2(listaTcbs);
			if(it->wait == tid){
				return it->tid;
			}	
		}
		while(NextFila2(listaTcbs)==0);
		return -1;
	}
	return -1;
}


/*troca de thread de bloqueada para apta
retorna 0 para sucesso, !=0 caso contrário
*/
int BloqsToAptos(int tid)
{
	TCB_t* it;
	if(FirstFila2(filaBloqs) == 0)
	{
		do
		{	
			it = GetAtIteratorFila2(filaBloqs);
			if(it->tid == tid){
				it->state = PROCST_APTO;
				DeleteAtIteratorFila2(filaBloqs);
				return insereAptos(it);
			}
		}
		while(NextFila2(filaBloqs) == 0);
	}
	return -1;
}

/*--------------------------------------------------------------------
Função: Insere um nodo na lista indicada, segundo o campo "prio" do TCB_t
	A fila deve estar ordenada (ou ter sido construída usado apenas essa funcao)
	O primeiro elemento da lista (first) é aquele com menor vamor de "prio"
Entra:	pfila -> objeto FILA2
	pnodo -> objeto a ser colocado na FILA2
Ret:	==0, se conseguiu
	!=0, caso contrário (erro)
--------------------------------------------------------------------*/
int	InsertByPrio(PFILA2 pfila, TCB_t *tcb) {
	TCB_t *tcb_it;
	
	if (FirstFila2(pfila)==0) {
		do {
			tcb_it = (TCB_t *) GetAtIteratorFila2(pfila);
			if (tcb->prio < tcb_it->prio) {
				return InsertBeforeIteratorFila2(pfila, tcb);
			}
		} while (NextFila2(pfila)==0);
	}	
	return AppendFila2(pfila, (void *)tcb);
}


/*-------------------------------------------------------------------
Função:	Insere thread na fila de aptos do escalonador
Ret:	==0, se conseguiu
	    !=0, caso contrário
-------------------------------------------------------------------*/
int insereAptos(TCB_t* thread){
	thread->state = PROCST_APTO;
    return InsertByPrio(filaAptos, thread);

}

/* retorna 0 caso sucesso, !=0 c.c. */
int insereTerminados(TCB_t* thread)
{	
	thread->state = PROCST_TERMINO;
	return AppendFila2(listaTerminados, thread);
}



int aptosVazia()
{
	return FirstFila2(filaAptos);
}


int tam()
{
	int cont = 0;
	
	if (FirstFila2(listaTcbs)==0) {
		do {
			GetAtIteratorFila2(listaTcbs);
			cont++;
		} while (NextFila2(listaTcbs)==0);
	}

	return cont;
}


/*-------------------------------------------------------------------
Função:	Insere thread na fila de bloqueados do escalonador
Ret:	==0, se conseguiu
	!=0, caso contrário
-------------------------------------------------------------------*/

int insereBloqs(TCB_t* thread){
	thread->state = PROCST_BLOQ;
    /// como não precisa se preocupar com a ordem na fila de bloqueados só insere no fim 
    return AppendFila2(filaBloqs, (void *)thread);
}



TCB_t* popFila(PFILA2 fila)
{
	// fila vazia?
	if(FirstFila2(fila) == 0)
	{
		TCB_t* first = (TCB_t*)GetAtIteratorFila2(fila);
		if(DeleteAtIteratorFila2(fila) != 0){
			printf("Erro removendo\n");
		}
		return first;
	}
	else{
		//printf("fila vazia");
		return NULL;
	}
}


TCB_t* popAptos()
{
	return popFila(filaAptos);
}


TCB_t* popBloqs()
{
	return popFila(filaAptos);
}

int removeBloqs(int tid)
{
	TCB_t* it;
	if(FirstFila2(filaBloqs) == 0)
	{
		do
		{	
			it = GetAtIteratorFila2(filaBloqs);
			if(it->tid == tid)
				return DeleteAtIteratorFila2(filaBloqs);
		}
		while(NextFila2(filaBloqs) == 0);
	}
	return -1;
}


void printTidsFilas() {
	TCB_t *tcb_it;
	printf("\nFila de aptos:");
	
	if (FirstFila2(filaAptos)==0) {
		do {
			tcb_it = GetAtIteratorFila2(filaAptos);
			printf("(id:%d, prio:%u, state: %d) -> \n", tcb_it->tid, tcb_it->prio, tcb_it->state);
		} while (NextFila2(filaAptos)==0);
	}	
	printf("NULL\n");
	printf("Fila de bloqueados:");
	
	if (FirstFila2(filaBloqs)==0) {
		do {
			tcb_it = GetAtIteratorFila2(filaBloqs);
			printf("(id:%d, prio:%u, state: %d) -> ", tcb_it->tid, tcb_it->prio, tcb_it->state);
		} while (NextFila2(filaBloqs)==0);
	}	
	printf("NULL\n");
	printf("Fila geral:");
	if(FirstFila2(listaTcbs) == 0){
		simpTcb* it;// = GetAtIteratorFila2(listaTcbs);
		do{
			it = GetAtIteratorFila2(listaTcbs);
			printf("(%d, %d) -> ", it->tid, it->wait);
		}
		while(NextFila2(listaTcbs) == 0);
	}
	printf("NULL\n\n");
	/*printf("Fila de terminados\n");
	if(FirstFila2(listaTerminados) == 0){
		simpTcb* it;// = GetAtIteratorFila2(listaTcbs);
		do{
			it = GetAtIteratorFila2(listaTerminados);
			printf("(%d) -> ", it->tid);
		}
		while(NextFila2(listaTerminados) == 0);
	}*/
	printf("NULL\n\n");
}

/*Busca uma thread em uma fila qualquer
retorna tid da thread quando encontra
e -1 quando não*/

int buscaEmFila(int tid, PFILA2 fila){
	TCB_t* it;
	if(FirstFila2(fila) == 0)
	{
		do
		{	
			it = GetAtIteratorFila2(fila);
			if(it->tid == tid)
				return it->tid;
		}
		while(NextFila2(fila) == 0);
	}
	return -1;	//quando nao encontrou a thread na fila

}

/*pesquisa uma tid nas listas de aptos e de bloqueados
retorna a tid caso encontre ou -1 c.c.*/
int existeThread(int tid){ 
    int busca = buscaEmFila(tid, filaAptos);
    if (busca == tid)
        return(busca);

    busca = buscaEmFila(tid, filaBloqs);
    if (busca == tid)
        return(busca);
    
    return (-1); //retorna -1 quando nao encontra nenhuma thread - NAO EXISTENCIA
}


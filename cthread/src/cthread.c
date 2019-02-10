#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
//#include "support.h"
//#include "cdata.h"
#include "cthread.h"
#include "escalonador.h"
//#include "tcb.h"
//#include "filas.h"
#include <string.h>

#define TAMANHO_PILHA 16384
#define MAXIMO_THREAD 100

int threadID = 0;
int debugPrints = 0;
int maintcb = 0;


/*--------------------------------------------------------------------
Função: CCREATE
Parâmetros:
start: ponteiro para a função que a thread executará.
arg: um parâmetro que pode ser passado para a thread na sua criação. (Obs.: é um único parâmetro. Se for necessário
passar mais de um valor deve-se empregar um ponteiro para uma struct)
Retorno:
Quando executada corretamente: retorna um valor positivo, que representa o identificador da thread criada
Caso contrário, retorna um valor negativo.
--------------------------------------------------------------------*/
int ccreate(void* (*start)(void*), void *arg, int prio){

	if(!getIniciado()){
		escalonadorInit();
	}

	if(!maintcb){
		if(0)
			printf("Criando thread de main\n");
		maintcb = 1;
		TCB_t* maintT = createTCB(0);
		getcontext(&maintT->context);
		setThreademExec(maintT);
		insereTcb(0);

	}

	TCB_t* t = createTCB(++threadID);
	createContext(t ,&execThread, start, arg, TAMANHO_PILHA);
	insereTcb(t->tid);

    //Garante o maximo de threads
    if (tam() < MAXIMO_THREAD){
        if (insereAptos(t) != 0) 
        	return -1;
        return t->tid;
    }
    else {
        printf("ATINGIU MAXIMO DE THREADS!");
        //free(t->context)   
        free(t);
        //free(contextoNovo);
        return -1;
    }

}

/*Função cyield
int cyield(void);
Retorno:
Quando executada corretamente: retorna 0 (zero)
Caso contrário, retorna um valor negativo.
*/

int cyield(void)
{
	if(!getIniciado()){
		escalonadorInit();
	}

    TCB_t* t = getThreadEmExec();
    t->prio += stopTimer();

	if(maintcb != 0 && insereAptos(t) != 0)
		return -1; //printf("Falha ao inserir\n");

	if(dispatcher() == -1){ //Nao tinha outra thread em aptos,
		return -1;
	}

	return 0;
}

/*Função cjoin
int cjoin(int tid);
Parâmetros:
tid: identificador da thread cujo término está sendo aguardado.
Retorno:
Quando executada corretamente: retorna 0 (zero)
Caso contrário, retorna um valor negativo
*/
int cjoin (int tid){	
	if(!getIniciado()){
		startTimer();
		escalonadorInit();
	}

	if(existeThread(tid) == -1){
		//printf("ERRO: Thread solicitada nao existe. Impossivel realizar cjoin\n");
		return -1;
	}

	if(isThreadWaitingFor(tid)==-1) /// já tem alguém esperando por essa tid?
	{	
		TCB_t* t = getThreadEmExec();
		t->prio += stopTimer();
		insereBloqs(t);

		setThreadWaiting(t->tid, tid);
		dispatcher();
		return 0;
	}
	else{
		//printf("ERRO: a thread ja eh esperada. Impossivel realizar cjoin\n");
		return -1;
	}
}

/*Função csem_init
int csem_init (csem_t *sem, int count);
Parâmetros:
sem: ponteiro para uma variável do tipo csem_t. Aponta para uma estrutura de dados que representa a variável semáforo.
count: valor a ser usado na inicialização do semáforo. Representa a quantidade de recursos controlados pelo semáforo.
Retorno:
Quando executada corretamente: retorna 0 (zero)
Caso contrário, retorna um valor negativo.
*/

int csem_init (csem_t *sem, int count)
{

	sem->count = count;
	PFILA2 filaSem = (PFILA2)malloc(sizeof(FILA2));

	if(CreateFila2(filaSem) != 0){
		return -1;
	}

	sem->fila = filaSem;

	if(sem->fila == NULL){
		printf("fila == NULL\n");
		return -1;
	}
	return 0;
}

/*Função cwait
Parâmetros:
sem: ponteiro para uma variável do tipo semáforo.
Retorno:
Quando executada corretamente: retorna 0 (zero)
Caso contrário, retorna um valor negativo.
*/

int cwait(csem_t *sem)
{
	if(sem->count > 0) /// há recurso disponível
	{
		sem->count--;
		return 0;
	}
	else /// não há recurso disponível
	{
		TCB_t* t = getThreadEmExec();
		t->prio+=stopTimer();
		t->state = PROCST_BLOQ;
		if(AppendFila2(sem->fila, t) != 0){
			return -1;//nao colocou na fila
		}

		dispatcher();
		sem->count--;
		return 0;
	}
}

/*Função csignal
Parâmetros:
sem: ponteiro para uma variável do tipo semáforo.
Retorno:
Quando executada corretamente: retorna 0 (zero)
Caso contrário, retorna um valor negativo.
*/

int csignal(csem_t *sem)
{
	sem->count++;
	if(FirstFila2(sem->fila) != 0)
		return 0;
	TCB_t* t= (TCB_t*)GetAtIteratorFila2(sem->fila);
	if (DeleteAtIteratorFila2(sem->fila)!=0)
		return -1;
	if (insereAptos(t) != 0)
		return -1;
	return 0;
}

/*Função cidentify
Parâmetros:
name: ponteiro para uma área de memória onde deve ser escrito um string que contém os nomes dos componentes do
grupo e seus números de cartão. Deve ser uma linha por componente.
size: quantidade máxima de caracteres que podem ser copiados para o string de identificação dos componentes do
grupo.
Retorno:
Quando executada corretamente: retorna 0 (zero)
Caso contrário, retorna um valor negativo.
*/

int cidentify (char *name, int size){
	
	if(strncpy(name, "Daniel Machado Nidejelski - 161886.\nJose Mario Reisswitz - 205798.\nValentina Montserrat - 208735\n", size) != NULL)
		return 0;
	else
		return -1;
}
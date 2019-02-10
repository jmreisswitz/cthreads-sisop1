#include "../include/support.h"
#include "../include/cthread.h"
#include "../include/cdata.h"
#include <stdio.h>

csem_t crit1, crit2;

char Scrit1[] = "crit1";
char Scrit2[] = "crit2";

void filas_printSem(csem_t* sem, char* nome)
{
	printf("\nsem->count = %d\n", sem->count);
	TCB_t* it;
	printf("Fila do semaforo %s:", nome);

	if(FirstFila2(sem->fila) == 0)
	{
		//printf("Tem algo na fuila\n");
		do{
			it = GetAtIteratorFila2(sem->fila);
			printf("(id:%d, prio:%u) -> ", it->tid, it->prio);
		}
		while(NextFila2(sem->fila) == 0);
	}
	printf("NULL\n\n");

}


void* foo1(int x)
{
	printf("entrando em sessao critica 1 em foo1...\n");
	printf("cwait = %d\n", cwait(&crit1));
	printf("Ocupou\n");
	
	cyield();
	//filas_printSem(&crit1, Scrit1);
	printf("Dentro de foo1 com x = %d\n", x);
	csignal(&crit1);
	printf("Depois de cisginal:");
	filas_printSem(&crit1, Scrit1);
	return;
}

void* foo2(int x)
{
	printf("Entrando em sessoa critica 1 em foo2..\n");
	printf("cwait = %d\n", cwait(&crit1));
	//filas_printSem(&crit1, Scrit1);
	cyield();
	printf("Dentro de foo2 com x = %d\n", x);
	csignal(&crit1);
	//filas_printSem(&crit1, Scrit1);
	return;
}

int main()
{
	/*
	FILA2 fila1;
	PFILA2 fila2;
	CreateFila2(&fila1);
	printf("criei");
	CreateFila2(fila2);
	*/
	printf("Iniciando main...\n");
	int cont = 0;
	
	int x = ccreate(foo1, (void*)cont++, 0);
	x = ccreate(foo2, (void*)cont++, 0);
	
	printf("init = %d\n", csem_init(&crit1, 1));

	cont= 10;
	cyield();
	cyield();
	cyield();
	cyield();

filas_printSem(&crit1, Scrit1);

	printf("Saindo de main...\n");
	return 0;
}
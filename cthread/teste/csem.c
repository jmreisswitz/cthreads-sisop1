#include <stdio.h>
#include "../include/cthread.h"
#include "../include/escalonador.h"
#include "../include/cdata.h"
#include "../include/support.h"

csem_t crit1, crit2;

void* foo1(int x)
{
	printf("entrando em sessao critica 1 em foo1...\n");
	printf("cwait = %d", cwait(&crit1));
	printf("Ocupou\n");
	cyield();
	printf("Dentro de foo1 com x = %d\n", x);
	csignal(&crit1);
	return;
}

void* foo2(int x)
{
	printf("Entrando em sessoa critica 1 em foo2..\n");
	printf("cwait = %d", cwait(&crit1));
	cyield();
	printf("Dentro de foo2 com x = %d\n", x);
	csignal(&crit1);
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


	printf("Saindo de main...\n");
	return 0;
}

/*
 *	Programa de exemplo de uso da biblioteca cthread
 *
 *	Versão 1.0 - 14/04/2016
 *
 *	Sistemas Operacionais I - www.inf.ufrgs.br
 *
 */

#include "../include/support.h"
#include "../include/cthread.h"
#include "../include/filas.h"
#include <stdio.h>

void* func0(void *arg) {
	printf("Eu sou a thread ID0 imprimindo %d\n", *((int *)arg));
	//filas_printTidsFilas();
	return;
}

void* func1(void *arg) {
	printf("Eu sou a thread ID1 imprimindo %d\n", *((int *)arg));
	//filas_printTidsFilas();
	return;
}

int main(int argc, char *argv[]) {

	int	id0, id1;
	int i;

	id0 = ccreate(func0, (void *)&i, 0);
	id1 = ccreate(func1, (void *)&i, 0);

	printf("Eu sou a main apos a criacao de ID0 e ID1\n");

	//filas_printTidsFilas();

	cjoin(id0);
	//filas_printTidsFilas();
	cjoin(id1);

	printf("saiu de id1\n");

	//filas_printTidsFilas();

	printf("Eu sou a main voltando para terminar o programa\n");
}


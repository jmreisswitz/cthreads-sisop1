#include "../include/support.h"
#include "../include/cthread.h"
#include "../include/filas.h"
#include <stdio.h>
#include <unistd.h>	

void foo1(int x)
{
	int i = 0;
	printf("Dentro de foo1 com x = %d\n", x);
	for(; i < 10; i++){
		printf("foo1: %d\n", cyield());
	}
	printf("Saindo de foo1 com i = %d\n", i);
}

void foo2(int x)
{
	int i = 0;
	printf("Entnrando em foo2\n");
	//sleep(1);
	filas_printTidsFilas();
	printf("Dentro de foo2 com x = %d\n", x);
	for(; i < 10; i++)
		printf("foo2: %d\n", cyield());
	printf("Saindo de foo2 com i = %d\n", i);
}

int main()
{
	printf("Iniciando main...\n");
	int cont = 0;

	
	int x = ccreate(foo1, cont++, 0);
	x = ccreate(foo2, cont++, 0);
	
	filas_printTidsFilas();

	sleep(1); /// dorme por 1 segs, "piorando" a prioridade de main
	cyield();

	filas_printTidsFilas();

	printf("Saindo de main...\n");
	return 0;
}
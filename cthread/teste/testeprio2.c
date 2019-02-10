#include <stdio.h>
#include <stdlib.h>
#include "../include/filas.h"
#include "../include/cdata.h"
#include "../include/cthread.h"
//#include "../include/support.h"
#include "../include/escalonador.h"

int libera = 0;

void foo1()
{
	printf("6 - Entrando em foo1 e liberando para foo2\n");
	cyield();
	printf("8 - voltando para foo1. Entrara em loop até a prioridade dessa ser pior que de foo2\n");
	printTidsFilas();
	while(libera == 0)
		cyield();
	printTidsFilas();
	printf("10 - terminando foo1\n");
}

void foo2()
{
	printf("7 - Entnrando em foo2, gastando tempo e libera a cpu\n");
	unsigned short int x = 1;
	while( x < 300 ){
		x++;
	}
	//printTidsFilas();
	cyield();
	libera = 1;
	printTidsFilas();
	printf("9 - voltando para foo2, e terminando ela\n");
}


int main()
{
	printf("1 - Iniciando main\n");
	printf("2 - gastando tempo na main, piorando a prioridade\n");
	//sleep(1);

	unsigned int x = 1;
	while( x < 1000 ){
		x++;
	}


	printf("3 - criando foo1. create = %d\n", ccreate(foo1,NULL,0));
	printf("4 - criando foo2. create = %d\n", ccreate(foo2,NULL,0));

	printf("5 - cedendo a cpu em main\n");

	printTidsFilas();

	cyield();

	//printTidsFilas();

	printf("11 - terminando main\n");

	return 0;

}
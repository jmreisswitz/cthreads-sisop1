#include "../include/support.h"
#include "../include/cthread.h"
#include <stdio.h>

void foo1(int x)
{
	printf("Dentro de foo1 com x = %d\n", x);
}

void foo2(int x)
{
	printf("Dentro de foo2 com x = %d\n", x);
}

int main()
{
	printf("Iniciando main...\n");
	int cont = 0;

	
	int x = ccreate(foo1, cont++, 0);
	x = ccreate(foo2, cont++, 0);
	
	cont= 10;
	cyield();
	cyield();
	cyield();
	cyield();


	printf("Saindo de main...\n");
	return 0;
}
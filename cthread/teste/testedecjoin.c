#include "../include/support.h"
#include "../include/cdata.h"
#include "../include/cthread.h"
#include <stdio.h>
#include <stdlib.h>

int i, j, a;
int tid1, tid2;

void* func1(){
  printf("func1\n");
  i = 10;
  return NULL;
}

void* func2(){
  printf("func2\n");
  j = 50;
  return NULL;
}

int main(int argc, char *argv[]){


  char nome[200] = "";
  //cidentify(nome, 50);
  printf("nome = %s\n", nome);


  tid1 = ccreate(func1, (void *) NULL,0);
  if (tid1 < 0){
    perror("Erro ao criar thread 1.");
    return -1;
  }

  tid2 = ccreate(func2, (void *) NULL,0);
  if (tid2 < 0){
    perror("Erro ao criar thread 2.");
    return -1;
  }

  cjoin(tid1);
  cjoin(tid2);
  a = cjoin(tid1);

  printf("\ni = %d  j = %d a= %d\n", i, j, a);
  puts("Teste encerrado.");

  return 0;
}
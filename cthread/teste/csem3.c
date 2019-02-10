#include<stdlib.h>
#include<unistd.h>

/*
Este teste cria 4 threads compartilhando a mesma fun¸c˜ao e vari´avel global
resource na main e faz cjoin para todas elas. Espera-se que, em momento
algum, o n´umero de threads utilizando o recurso (mensagem que ´e impressa na
tela) seja maior do que o valor do recurso dispon´ıvel. Ainda, todas as threads
devem ser executadas e o programa apenas ser´a finalizado ap´os o t´ermino de
todas essas threads, imprimindo ”Fim” quando retornar `a main e encerrar sua
execu¸c˜ao.

PASSOU
*/

#include "../include/support.h"
#include "../include/cthread.h"
#include <stdio.h>


#define   CHAIRS 5

time_t end_time;

void sleepao() {
     int i = 0;

     i = rand()%5 + 1;
     for (; i<0; i--) cyield();
     return;
}

csem_t sem_resource;
int resource = 0;

void getResource(void *arg) {
  cwait(&sem_resource);
  resource++;
  sleep(1);
  cyield();
  printf("Threads using the resource = %d ...\n", resource);
  resource--;
  csignal(&sem_resource);
}

int main(int argc, char **argv)
{
    int tid1, tid2, tid3, tid4;

    csem_init(&sem_resource, 1);

    tid1 = ccreate (getResource, (void *) NULL, 0);
    if (tid1 < 0 )
       perror("Erro na criação do tid1...\n");

    tid2 = ccreate (getResource, (void *) NULL, 0);
    if (tid2 < 0 )
      perror("Erro na criação do tid2...\n");

    tid3 = ccreate (getResource, (void *) NULL, 0);
      if (tid3 < 0 )
        perror("Erro na criação do tid3...\n");

    tid4 = ccreate (getResource, (void *) NULL, 0);
      if (tid4 < 0 )
        perror("Erro na criação do tid4...\n");

    cjoin(tid1);
    cjoin(tid2);
    cjoin(tid3);
    cjoin(tid4);

    puts("Fim");

    exit(0);
}
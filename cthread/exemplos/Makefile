#
# Makefile para programas exemplo
# 

CC=gcc
LIB_DIR=../lib

all: exemplo mandel teste_vetor barbeiro filosofos prodcons series

exemplo: exemplo.c $(LIB_DIR)/libcthread.a
	$(CC) -o exemplo exemplo.c -L$(LIB_DIR) -lcthread

teste_vetor: teste_vetor.c $(LIB_DIR)/libcthread.a
	$(CC) -o teste_vetor teste_vetor.c -L$(LIB_DIR) -lcthread

mandel: mandel.c $(LIB_DIR)/libcthread.a
	$(CC) -o mandel mandel.c -L$(LIB_DIR) -lcthread -lm

barbeiro: barbeiro.c $(LIB_DIR)/libcthread.a
	$(CC) -o barbeiro barbeiro.c -L$(LIB_DIR) -lcthread -lm

filosofos: filosofos.c $(LIB_DIR)/libcthread.a
	$(CC) -o filosofos filosofos.c -L$(LIB_DIR) -lcthread -lm

prodcons: prodcons.c $(LIB_DIR)/libcthread.a
	$(CC) -o prodcons prodcons.c -L$(LIB_DIR) -lcthread -lm

series: series.c $(LIB_DIR)/libcthread.a
	$(CC) -o series series.c -L$(LIB_DIR) -lcthread -lm
	
clean:
	rm -rf exemplo mandel teste_vetor barbeiro filosofos prodcons series *.o *~





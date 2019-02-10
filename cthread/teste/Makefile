#
# Makefile para programas exemplo
# 

CC=gcc
LIB_DIR=../lib

all: csem2 teste1 teste2 csem3 testedesemaforoecjoin testeprio testetcb

csem2: csem2.c $(LIB_DIR)/libcthread.a
	$(CC) -g -o csem2 csem2.c -L$(LIB_DIR) -lcthread
	
teste1: teste1.c $(LIB_DIR)/libcthread.a
	$(CC) -g -o teste1 teste1.c -L$(LIB_DIR) -lcthread

teste2: teste2.c $(LIB_DIR)/libcthread.a
	$(CC) -g -o teste2 teste2.c -L$(LIB_DIR) -lcthread

csem3: csem3.c $(LIB_DIR)/libcthread.a
	$(CC) -g -o csem3 csem3.c -L$(LIB_DIR) -lcthread

testedesemaforoecjoin: testedesemaforoecjoin.c $(LIB_DIR)/libcthread.a
	$(CC) -g -o testedesemaforoecjoin testedesemaforoecjoin.c -L$(LIB_DIR) -lcthread

testeprio: testeprio.c $(LIB_DIR)/libcthread.a
	$(CC) -g -o testeprio testeprio.c -L$(LIB_DIR) -lcthread

testetcb: testetcb.c $(LIB_DIR)/libcthread.a
	$(CC) -g -o testetcb testetcb.c -L$(LIB_DIR) -lcthread

clean:
	rm *.o 





# Makefile

#Author: Marie
#Date: Start 19/04/2021
#About: Makefile of list of child system for monte carlo

CC = gcc
CFLAGS =  -Wall -O3
LDLIBS =  -lm


all: main

main :  ../create_childs.o  ../mcts.o  ../../../../common/c/rules/pieces.o ../check_and_pat_for_AI.o ../../../../common/c/rules/plate.o

main/.o: ../create_childs.h ../mcts.h   ../../../../common/c/rules/pieces.h ../check_and_pat_for_AI.h ../../../../common/c/rules/plate.h 

clean:
	${RM} ../*.o
	${RM} ../*.d
	${RM} ../../../../common/c/rules/*.o
	${RM} ../../../../common/c/rules/*.d
	${RM} main


# END

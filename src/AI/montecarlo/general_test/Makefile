# Makefile

#Author: Marie
#Date: Start 19/04/2021
#About: Makefile of list of child system for monte carlo

CC = gcc
CFLAGS =  -Wall -O3
LDLIBS =  -lm


all: main

main :  ../search_and_play/monte_carlo_method.o  ../search_and_play/search_and_play.o ../tree/mcts.o ../tree/create_childs.o  ../../../common/c/rules/pieces.o ../../../common/c/rules/check_and_pat.o ../../../common/c/rules/plate.o  ../tree/check_and_pat_for_AI.o

main/.o: ../search_and_play/monte_carlo_method.h  ../search_and_play/search_and_play.h ../tree/mcts.h ../tree/create_childs.h  ../../../common/c/rules/pieces.h ../../../common/c/rules/check_and_pat.h ../../../common/c/rules/plate.h  ../tree/check_and_pat_for_AI.h

clean:

	${RM} ../tree/*.o
	${RM} ../tree/*.d
	${RM} ../search_and_play/*.o
	${RM} ../search_and_play/*.d
	${RM} ../../../common/c/rules/*.o
	${RM} ../../../common/c/rules/*.d
	${RM} main


# END

# Makefile


CC = gcc
CFLAGS =  -Wall -O3
LDLIBS =  -lm


all: main

main :  ../create_childs.o  ../../../../common/c/rules/pieces.o ../../../../common/c/rules/check_and_pat.o ../../../../common/c/rules/plate.o

main/.o: ../create_childs.h ../../../../common/c/rules/pieces.h ../../../../common/c/rules/check_and_pat.h ../../../../common/c/rules/plate.h

clean:
	${RM} ../*.o
	${RM} ../*.d
	${RM} ../../../../common/c/rules/*.o
	${RM} ../../../../common/c/rules/*.d
	${RM} main


# END

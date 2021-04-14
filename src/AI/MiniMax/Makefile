# Makefile

CC = gcc -std=c99
CFLAGS = -Wall -Wextra -lssl

all: minimax

minimax : testing.o minimax.o ../../common/c/rules/check_and_pat.o ../../common/c/rules/pieces.o ../../common/c/rules/plate.o

.PHONY: clean

clean:
	${RM} mainpage
	${RM} *.o
	${RM} *.d

# END

# Makefile

CC = gcc -lsqlite3
CFLAGS = `pkg-config --cflags gtk+-3.0` -Wall -O3
LDLIBS = `pkg-config --libs gtk+-3.0`

all: mainpage

mainpage : mainpage.o

.PHONY: clean

clean:
	${RM} mainpage
	${RM} *.o
	${RM} *.d

# END

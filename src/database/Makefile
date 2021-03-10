CC = gcc -lsqlite3 -std=c99
CFLAGS = -Wall -Wextra -lssl

all: test_create

test_create : SHA.o create_db.o functions_db.o test_create.o

.PHONY: clean

clean:
	${RM} test_create test_create.o
	${RM} *.o
	${RM} *.d

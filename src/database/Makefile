CC = gcc -lsqlite3 -std=c99
CFLAGS = -Wall -Wextra -lssl

all: create_db MD5 MD5_2 SHA1

create_db: create_db.o
SHA: SHA.o

.PHONY: clean

clean:
	${RM} create_db create_db.o
	${RM} SHA SHA.o

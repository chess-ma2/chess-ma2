CC = gcc -lsqlite3 -std=c99
CFLAGS = -Wall -Wextra -lssl

all: game1

game1 : game1.o ../../../database/create_db.o ../../../database/functions_db.o ../rules/pieces.o ../rules/check_and_pat.o ../rules/plate.o ../../../database/SHA.o version1.o

.PHONY: clean

clean:
	${RM} game1 game1.o
	${RM} *.o
	${RM} *.d
	${RM} ../../../database/*.d
	${RM} ../../../database/*.o
	${RM} ../rules/*.d
	${RM} ../rules/*.o
	${RM} chess.db

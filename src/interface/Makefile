# Makefile

#CC = gcc -lsqlite3
#CFLAGS = `pkg-config --cflags gtk+-3.0` -Wall -O3
#LDLIBS = `pkg-config --libs gtk+-3.0`

#all: mainpage

#mainpage : mainpage.o Local1.o ../database/create_db.o

#.PHONY: clean

#clean:
#	${RM} mainpage
#	${RM} *.o
#	${RM} *.d

# END

all: clean build
		@echo "[Chess(ma)² - Gtk] All sources game version 1 tasks DONE!"

clean:
		@echo "[Chess(ma)² - Gtk] Start to clean..."
		@rm -f "game" "chess.db"
		@echo "[Chess(ma)² - Gtk] End to clean!"

build:
		@echo "[Chess(ma)² - Gtk] Start build common sources..."
		@gcc -pthread -lsqlite3  -O3 `pkg-config --libs gtk+-3.0` `pkg-config --cflags gtk+-3.0` mainpage.c \
	    -o "game"
		@echo "[Chess(ma)² - Gtk] End build sources!"

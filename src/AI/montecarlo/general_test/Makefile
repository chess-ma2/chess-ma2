# Makefile

#Author: Marie
#Date: Start 19/04/2021
#About: Makefile of list of child system for monte carlo

all: clean build
		@echo "[Chess(ma)² - Montecarlo] All sources tasks DONE!"

clean:
		@echo "[Chess(ma)² - Montecarlo] Start to clean..."
		@rm -f "main" "*.o" "../tree/*.o" "../search_and_play/*.o"
		@echo "[Chess(ma)² - Montecarlo] End to clean!"

build:
		@echo "[Chess(ma)² - Montecarlo] Start build common sources..."
		@gcc -pthread -lsqlite3 -Wall -O3 main.c \
	    -o "main"
		@echo "[Chess(ma)² - Montecarlo] End build sources!"



# END

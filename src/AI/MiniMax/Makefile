all: clean build
		@echo "[Chess(ma)² - MiniMax] All sources game version 1 tasks DONE!"

clean:
		@echo "[Chess(ma)² - MiniMax] Start to clean..."
		@rm -f "minimax" "*.o" "minimax.o" "testing.o"
		@echo "[Chess(ma)² - MiniMax] End to clean!"

build:
		@echo "[Chess(ma)² - MiniMax] Start build common sources..."
		@gcc -pthread -lsqlite3 -Wall -O3 testing.c \
	    -o "minimax"
		@echo "[Chess(ma)² - MiniMax] End build sources!"

all: clean build
		@echo "[Chess(ma)² - game] All sources game version 1 tasks DONE!"

clean:
		@echo "[Chess(ma)² - game] Start to clean..."
		@rm -f "game.out" "chess.db"
		@echo "[Chess(ma)² - game] End to clean!"

build:
		@echo "[Chess(ma)² - game] Start build common sources..."
		@mkdir -p ../../../target/
		@gcc -pthread -lsqlite3 -Wall -O3 game1.c \
	    -o "game.out"
		@echo "[Chess(ma)² - game] End build sources!"

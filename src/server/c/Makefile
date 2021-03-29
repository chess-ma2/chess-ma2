#Author: Marine
#Date: Start 01/03/2021
#About: Makefile of the server system

all: clean build
	@echo "[Chess(ma)² - Server] All sources server tasks DONE!"

clean:
	@echo "[Chess(ma)² - Server] Start to clean..."
	@rm -f "../../../target/server.out"
	@echo "[Chess(ma)² - Server] End to clean!"

build:
	@echo "[Chess(ma)² - Server] Start build server sources..."
	@mkdir -p ../../../target/
	@gcc -pthread -Wall -O3 main.c \
    -o "../../../target/server.out"
	@echo "[Chess(ma)² - Server] End build sources!"
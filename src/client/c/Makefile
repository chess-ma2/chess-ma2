#Author: Marine
#Date: Start 01/03/2021
#About: Makefile of the client system

all: clean build
	@echo "[Chess(ma)² - Client] All sources common tasks DONE!"

clean:
	@echo "[Chess(ma)² - Client] Start to clean..."
	@rm -f "../../../target/client.out"
	@echo "[Chess(ma)² - Client] End to clean!"

build:
	@echo "[Chess(ma)² - Client] Start build client sources..."
	@mkdir -p ../../../target/
	@gcc -pthread -Wall -O3 main.c \
    -o "../../../target/client.out"
	@echo "[Chess(ma)² - Client] End build sources!"
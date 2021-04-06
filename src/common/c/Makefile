#Author: Marine
#Date: Start 01/03/2021
#About: Makefile of the common system

all: clean build
	@echo "[Chess(ma)² - Common] All sources common tasks DONE!"

clean:
	@echo "[Chess(ma)² - Common] Start to clean..."
	@rm -f "../../../target/common.out"
	@echo "[Chess(ma)² - Common] End to clean!"

build:
	@echo "[Chess(ma)² - Common] Start build common sources..."
	@mkdir -p ../../../target/
	@gcc -pthread -lsqlite3 -Wall -O3 main.c \
    -o "../../../target/common.out"
	@echo "[Chess(ma)² - Common] End build sources!"

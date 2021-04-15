#Author: Antoine
#Date: Start 15/04/2021
#About: Makefile of the montecarlo system

all: clean build
	@echo "[Chess(ma)² - AI Common] All sources AI Common tasks DONE!"

clean:
	@echo "[Chess(ma)² - AI Common] Start to clean..."
	@rm -f "../../../target/AICommon.out"
	@echo "[Chess(ma)² - AI Common] End to clean!"

build:
	@echo "[Chess(ma)² - AI Common] Start build AI Common sources..."
	@mkdir -p ../../../target/
	@gcc -pthread -lsqlite3 -Wall -O3 main.c \
    -o "../../../target/AICommon.out"
	@echo "[Chess(ma)² - AI Common] End build sources!"

#Author: Antoine
#Date: Start 13/04/2021
#About: Makefile of the montecarlo system

all: clean build
	@echo "[Chess(ma)² - MonteCarlo] All sources MonteCarlo tasks DONE!"

clean:
	@echo "[Chess(ma)² - MonteCarlo] Start to clean..."
	@rm -f "../../../target/MonteCarlo.out"
	@echo "[Chess(ma)² - MonteCarlo] End to clean!"

build:
	@echo "[Chess(ma)² - MonteCarlo] Start build common sources..."
	@mkdir -p ../../../target/
	@gcc -pthread -lsqlite3 -Wall -O3 main.c \
    -o "../../../target/MonteCarlo.out"
	@echo "[Chess(ma)² - MonteCarlo] End build sources!"

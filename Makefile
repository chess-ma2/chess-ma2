#Author: Marine
#Date: Start 01/03/2021
#About: Main makefile of the system, can be run sub Makefile

#Launch full make all of sub makes
all:
	@echo "[Chess(ma)² - Global] Launch Full build..."
	make -s -f Makefile build
	@echo "[Chess(ma)² - Global] Make all of sources DONE!"

#Launch full make clean of sub makes
clean:
	@echo "[Chess(ma)² - Global] Launch Full clean..."
	make -s -C src/common/c/ -f Makefile clean
	make -s -C src/server/c/ -f Makefile clean
	make -s -C src/client/c/ -f Makefile clean
#	make -s -C src/AI/montecarlo/ -f Makefile clean
	@rm -rf "target/"
	@echo "[Chess(ma)² - Global] Make clean of sources DONE!"

#Launch build of sources
build: clean
	@echo "[Chess(ma)² - Global] Launch build..."
	make -s -C src/common/c/ -f Makefile build
	make -s -C src/server/c/ -f Makefile build
	make -s -C src/client/c/ -f Makefile build
	make -s -C src/AI/montecarlo/ -f Makefile build
	@echo "[Chess(ma)² - Global] Final build is in target directory!"

xor:
	@echo "[Chess(ma)² - MonteCarlo - XOR] Start build MonteCarlo XOR sources..."
	@mkdir -p target/
	@gcc -pthread -lsqlite3 -lm -Wall -O3 src/AI/montecarlo/network/xor/xor_demo.c \
    -o "target/MonteCarloXOR.out"
	@echo "[Chess(ma)² - MonteCarlo - XOR] End build sources!"

mctsn:
	@echo "[Chess(ma)² - MonteCarlo - Network] Start build MonteCarlo network sources..."
	@mkdir -p target/
	@gcc -pthread -lsqlite3 -lm -Wall -O3 src/AI/montecarlo/network/tree/main.c \
    -o "target/MonteCarloNetwork.out"
	@echo "[Chess(ma)² - MonteCarlo - Network] End build sources!"
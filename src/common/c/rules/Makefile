all: clean build
	@echo "[Chess(ma)² - Common] All sources common tasks DONE!"

clean:
	@echo "[Chess(ma)² - Common] Start to clean..."
	@rm -f "../../../target/common.out"
	@echo "[Chess(ma)² - Common] End to clean!"

build:
	@echo "[Chess(ma)² - Common] Start build common sources..."
	@mkdir -p ../../../target/
	@gcc -pthread -lsqlite3 -Wall -O3 rules.c \
    -o "rules"
	@echo "[Chess(ma)² - Common] End build sources!"

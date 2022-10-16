.PHONY: all build rebuild check memtest clean

all: clean check build memtest

clean:
	rm -rf ./server/build
	rm valgrind.log

check:
	./scripts/linters/run.sh

build:
	./build.sh

rebuild: clean build

memtest:
	./scripts/valgrind.sh ./server/build/server --memcheck

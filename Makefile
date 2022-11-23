.PHONY: all build rebuild check memtest clean

all: clean check build memtest

clean:
	rm -rf */build

check:
	./scripts/run_linters.sh

build:
	./scripts/build.sh

rebuild: clean build

memtest:
	./scripts/valgrind.sh ./server/build/server --memcheck
	./scripts/valgrind.sh ./client/build/client --memcheck

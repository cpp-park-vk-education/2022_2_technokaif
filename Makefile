.PHONY: all build rebuild check memtest clean

all: clean check build memtest

clean:
	rm -rf ./server/build

check:
	./scripts/linters/run.sh

build:
	./build.sh -DMEMCHECK=OFF

rebuild: clean build

test:
	./build.sh -DMEMCHECK=OFF
	./tests.sh

memtest:
	./build.sh -DMEMCHECK=ON
	./tests.sh
	

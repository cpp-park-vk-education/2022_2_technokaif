.PHONY: all build rebuild check memtest clean

all: clean check build memtest

clean:
	rm -rf */build

check:
	./scripts/linters/run.sh

build:
	./scripts/build.sh -DMEMCHECK=OFF

rebuild: clean build

test:
	./scripts/build.sh -DMEMCHECK=OFF
	./scripts/tests.sh

memtest:
	./scripts/build.sh -DMEMCHECK=ON
	./scripts/tests.sh

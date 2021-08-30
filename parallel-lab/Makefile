UID=UIDUIDUID

all: nbody

nbody: nbody.cpp
	g++ --std=c++11 -fopenmp -O3 -o nbody nbody.cpp

test: all
	tests/test.sh

package: all
	tests/package.sh $(UID)

clean:
	rm -f nbody *.o UIDUIDUID.tar.gz
	ls | grep -P "^[0-9]{9}.tar.gz$$" | xargs -d"\n" rm -f

.PHONY: all test package clean

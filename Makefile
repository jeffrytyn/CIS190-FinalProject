all: a.out

a.out: test.cpp mergesort.hpp countingsort.hpp
	g++-10 -g -Wall -std=c++20 test.cpp

test: a.out
	./a.out

clean:
	rm a.out

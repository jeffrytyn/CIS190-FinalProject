all: main.o

main.o: main.cpp tetromino.o
	g++-10 -g -Wall -std=c++20 -o main.o main.cpp tetromino.o -lsfml-window -lsfml-graphics -lsfml-system 

tetromino.o: Tetromino/Tetromino.hpp Tetromino/Tetromino.cpp
	g++-10 -std=c++20 -c Tetromino/Tetromino.cpp

clean:
	rm -f *.o

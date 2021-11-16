all: main.o

main.o: main.cpp board.o tetromino.o game.o
	g++-10 -g -Wall -std=c++20 -o main.o main.cpp board.o tetromino.o  game.o -lsfml-window -lsfml-graphics -lsfml-system 

board.o: Board/Board.hpp Board/Board.cpp
	g++-10 -std=c++20 -c Board/Board.cpp

tetromino.o: Tetromino/Tetromino.hpp Tetromino/Tetromino.cpp
	g++-10 -std=c++20 -c Tetromino/Tetromino.cpp

game.o: Game/Game.hpp Game/Game.cpp
	g++-10 -std=c++20 -c Game/Game.cpp

clean:
	rm -f *.o

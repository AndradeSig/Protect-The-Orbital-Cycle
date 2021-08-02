all:
	g++ -c Source/Main/game.cpp
	g++ game.o -o orbitalcycle_linux -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
	./orbitalcycle_linux

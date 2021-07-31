all:
	g++ -c Source/Main/game.cpp
	g++ game.o -o JaajGame -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
	./JaajGame
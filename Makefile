all:
	g++ -c Source/Main/game.cpp
	g++ game.o -o Game/JaajGame -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
	./Game/JaajGame
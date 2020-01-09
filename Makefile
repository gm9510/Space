CC = g++

SFML = -lsfml-graphics -lsfml-window -lsfml-system

objects = main.o GAME.o SOLID.o PLAYER.o 

sfml.app : $(objects)
	$(CC) $(objects) -o sfml.app $(SFML)
main.o : main.cpp header.h
	$(CC) -c main.cpp
GAME.o : GAME.cpp header.h
	$(CC) -c GAME.cpp
SOLID.o : SOLID.cpp header.h
	$(CC) -c SOLID.cpp
PLAYER.o : PLAYER.cpp header.h
	$(CC) -c PLAYER.cpp
clean :
	-rm sfml.app $(objects)

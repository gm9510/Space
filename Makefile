CC = g++ -std=c++11

SFML = -lsfml-graphics -lsfml-window -lsfml-system

objects = main.o GEngine.o VirtualState.o PlayState.o MenuState.o SOLID.o PLAYER.o BUTTON.o TEXT.o

sfml.app : $(objects)
	$(CC) $(objects) -o sfml.app $(SFML)
main.o : main.cpp GEngine.h
	$(CC) -c main.cpp
GEngine.o : GEngine.cpp GEngine.h GState.h
	$(CC) -c GEngine.cpp
VirtualState.o : VirtualState.cpp GState.h GEngine.h
	$(CC) -c VirtualState.cpp
PlayState.o : PlayState.cpp GState.h GEngine.h
	$(CC) -c PlayState.cpp
SOLID.o : SOLID.cpp SOLID.h
	$(CC) -c SOLID.cpp
PLAYER.o : PLAYER.cpp SOLID.h
	$(CC) -c PLAYER.cpp
MenuState.o : MenuState.cpp GState.h GEngine.h
	$(CC) -c MenuState.cpp
BUTTON.o : BUTTON.cpp UIText.h
	$(CC) -c BUTTON.cpp
TEXT.o : TEXT.cpp UIText.h
	$(CC) -c TEXT.cpp
clean :
	-rm sfml.app $(objects)

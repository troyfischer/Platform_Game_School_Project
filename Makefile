 
NAME = platformer

CC = g++

LINKER_FLAGS = -lSDL2 -std=c++11


all: main.o Window.o
	$(CC) main.o Window.o $(LINKER_FLAGS) -o $(NAME)

main.o: main.cpp
	$(CC) main.cpp -c $(LINKER_FLAGS)

Window.o: Window.cpp
	$(CC) Window.cpp -c $(LINKER_FLAGS)

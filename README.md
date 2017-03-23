Definition
The definition of the system is a platform based game that will include a character that must traverse the map while avoiding enemies. This system is important for entertainment purposes. The story will be based around a character trapped inside of a dungeon and trying to escape.
The program will use the Simple DirectMedia Layer library. 

Analysis
The inputs will come from the keyboard, specifically the W, A, D and space keys. The outputs will be movement of the character either up, left or right respectively and the space key for starting the game. 

Logic:
1.	Initialize window
2.	Input data from keyboard
3.	Process data into movement of the character
4.	Check for collisions
5.	Output the character’s movement to the screen

Design
The design will require 4 modules:
1.	Window
2.	Map 
3.	Character
4.	Enemies & Items

The shared class among all modules is the Hitbox class. The shared methods across most modules are the get_x(), get_y() and get_hitbox() methods.

Execution Plan
The best way to divide the task for our group will be for one person to work on the Window module and assign two people to each remaining module. The person working on the Window will also be able to float around and help anybody with the remaining modules. 

The makefile will look something like this:
TARGET = Platformer.o Window.o Map.o Platform.o Character.o Enemy.o Item.o

NAME = platformer

CC = g++

LINKER_FLAGS = -lSDL2 -std=c++11


all: TARGET
	$(CC) TARGET $(LINKER_FLAGS) -o $(NAME)

Platformer.o: platformer.cpp
	$(CC) platformer.cpp -c $(LINKER_FLAGS)

Window.o: Window.cpp
	$(CC) Window.cpp -c $(LINKER_FLAGS)

Map.o: Map.cpp	
	$(CC) Map.cpp -c $(LINKER_FLAGS)

Platform.o:	Platform.cpp
	$(CC) Platform.cpp -c $(LINKER_FLAGS)

Character.o: Character.cpp	
	$(CC) Character.cpp -c $(LINKER_FLAGS)

Enemy.o: Enemy.cpp
	$(CC) Enemy.cpp -c $(LINKER_FLAGS)

Item.o: Item.cpp
	$(CC) Item.cpp -c $(LINKER_FLAGS)

Deadlines:
March 26 - Fully functioning window with player movement - Window + Character module
April 2 - Ability to pick-up items and lose lives when contact is made with enemies - Item + Enemy module
April 9 - Fully created map - Map module
April 16 - Working platform game - completed project

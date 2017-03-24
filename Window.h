//Window class
#ifndef _WINDOW_H
#define _WINDOW_H
#include <SDL2/SDL.h>
#include <string>

class Window
{	
	const int window_width = 640;
	const int window_height = 480;
	SDL_Window *window;
	SDL_Surface *screen;
	bool initialize();
	bool addSurface();
	void gameLoop();
	void close();
	void frameRate(float &start_tick);
	void regulateFrameRate(float start_tick);
	bool handleEvent();
	void logError(const std::string msg);
public:
	Window();
	void runGame();
	void addCharacter();
	//not sure below is necessary
	SDL_Window* get_window();
	SDL_Surface* get_surface();
};

#endif //_WINDOW_H
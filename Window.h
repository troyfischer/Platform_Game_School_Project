//Window class
#ifndef _WINDOW_H
#define _WINDOW_H
#include <SDL2/SDL.h>
#include <string>

class Window
{	
	const int screen_width = 640;
	const int screen_height = 480;
	SDL_Window *window;
	SDL_Surface *screen;
	SDL_Event event;

public:
	Window();
	bool init();
	bool addSurface();
	void close();
	SDL_Event getEvent();
	//not sure below is necessary
	SDL_Window* get_window();
	SDL_Surface* get_surface();
};

#endif //_WINDOW_H
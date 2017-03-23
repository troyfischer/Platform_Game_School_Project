//Window class
#ifndef _WINDOW_H
#define _WINDOW_H
#include <SDL2/SDL.h>
#include <string>

class Window
{	
	//other changes
	const int screen_width = 640;
	const int screen_height = 400;
	SDL_Window* window;
	SDL_Surface* screenSurface;
	SDL_Surface* image;

public:
	Window();
	bool init();
	bool load(std::string filePath);
	void close();
	SDL_Window* get_window();
	SDL_Surface* get_surface();
};

#endif //_WINDOW_H
//Window implementation
#include "Window.h"

Window::Window()
{
	window = 0;
	screen = 0;
}

bool Window::init()
{
	bool success = true;

	//Initialize SDL
	if(SDL_Init( SDL_INIT_EVERYTHING ) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height, SDL_WINDOW_SHOWN);
		if( window == NULL )
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
	}
	return success;
}

bool Window::addSurface()
{
	screen = SDL_GetWindowSurface(window);
	if (screen == 0)
	{
		printf("SDL adding surface error: %s\n", SDL_GetError());
		return 0;
	}
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 255));
	SDL_UpdateWindowSurface(window);
	return 1;
}

void Window::close()
{
	SDL_DestroyWindow( window) ;
	window = 0;

	SDL_Quit();
}

SDL_Event Window::getEvent()
{
	return event;
}
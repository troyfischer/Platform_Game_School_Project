//Window implementation
#include "Window.h"

//public methods
Window::Window()
{
	window = 0;
	screen = 0;
}

void Window::runGame()
{
	if (initialize())
	{
		gameLoop();
	}
}

//private methods
bool Window::initialize()
{
	bool success = true;

	//Initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
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

void Window::gameLoop()
{
	bool running = true;
	//variable for calculating frame rate
	float start_tick1 = SDL_GetTicks();
	while (running)
	{
		float start_tick = SDL_GetTicks();
		SDL_Event event;
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				close();
				break;
			}
		}
		regulateFrameRate(start_tick);
	}
}

void Window::close()
{
	SDL_DestroyWindow(window) ;
	SDL_Quit();
}

void Window::frameRate(float &start_tick)
{
	static int frames = 0;
	++frames;
	float end_tick = SDL_GetTicks();

	if (end_tick - start_tick >= 1000)
	{
		printf("FPS: %d\n", frames);
		frames = 0;
		start_tick = end_tick;
	}
}

void Window::regulateFrameRate(float start_tick)
{
	float FPS = 60.0;

	if ((1000.0 / FPS) > (SDL_GetTicks() - start_tick))
	{
		SDL_Delay((1000.0 / FPS) - (SDL_GetTicks() - start_tick)); 
	}

}

// void Window::addCharacter(Character character)
// {
// 	SDL_Rect tempRect;
// 	tempRect.x = 640/2;
// 	tempRect.y = 480/2;
// 	tempRect.w = 32;
// 	tempRect.h = 32;

// 	SDL_Surface *tempSurf;
// 	tempSurf = SDL_GetWindowSurface(window);



// 	SDL_Rect charRect = character.getRect();
// 	SDL_BlitSurface(screen, &charRect, )
// }
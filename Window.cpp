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
	/* Initialize SDL and Create Window */
	bool success = true;

	//Initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		logError("SDL_Init");
		success = false;
	}
	else
	{
		//Create window
		window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_SHOWN);
		if( window == NULL )
		{
			logError("SDL_CreateWindow");
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
		logError("SDL_GetWindowSurface");
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
		running = handleEvent();
		if (!running)
		{
			break;
		}
		regulateFrameRate(start_tick);
		frameRate(start_tick1);
	}
}

void Window::close()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
	exit(0);
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

bool Window::handleEvent()
{
	//returns 1 for continue gameLoop and 0 for end gameLoop
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			close();
			return 0;
		}
	}
	return 1;
}

void Window::logError(const std::string msg)
{
	printf("%s error: %s\n", msg.c_str(), SDL_GetError());
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
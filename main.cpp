/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>
#include "Window.h"

int main(int argc, char const *argv[])
{
	Window window;
	
	if ( window.init ())
	{
		bool running = true;
		while ( running )
		{
			// window.addSurface();
			SDL_Event event;
			if ( SDL_PollEvent( &event ) )
			{
				if ( event.type == SDL_QUIT)
				{
					running = false;
					window.close();
				}
			}
		}
	}
	return 0;
}
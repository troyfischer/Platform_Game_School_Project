#include "Platform.hpp"

Platform::Platform()
{
    //default size for each platform
    _platform.w = 75;
    _platform.h = 10;
}

void Platform::setPlatform(int x, int y)
{
    _platform.x = x;
    _platform.y = y;
}

void Platform::show(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &_platform);
}

int Platform::getX() { return _platform.x; }
int Platform::getY() { return _platform.y; }
int Platform::getW() { return _platform.w; }
int Platform::getH() { return _platform.h; }


#include "Platform.hpp"

Platform::Platform()
{
    //default size for each platform
    _platform.h = 5;
}

Platform::~Platform()
{
}

void Platform::setPlatform(int x, int y, int w, int level)
{
    _platform.x = x;
    _platform.y = y;
    _platform.w = w;
    
    
    _levelID = level;
}

void Platform::show(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_RenderFillRect(renderer, &_platform);
}

int Platform::getX() { return _platform.x; }
int Platform::getY() { return _platform.y; }
int Platform::getW() { return _platform.w; }
int Platform::getH() { return _platform.h; }
int Platform::getLevelID() { return _levelID; }

SDL_Rect * Platform::getRect() { return &_platform; }

#ifndef Platform_hpp
#define Platform_hpp

#include <stdio.h>
#include <SDL2/SDL.h>

class Platform
{
private:
    SDL_Rect _platform;
    int _levelID;
public:
    Platform();
    ~Platform();
    void setPlatform(int x, int y, int w, int level);
    void show(SDL_Renderer *renderer);
    
    int getX();
    int getY();
    int getW();
    int getH();
    int getLevelID();
    
    SDL_Rect * getRect();
    
    
};

#endif /* Platform_hpp */

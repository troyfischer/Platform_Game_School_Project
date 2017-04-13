#ifndef Map_hpp
#define Map_hpp

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "header.h"

class Map
{
private:
    std::vector<Platform> platforms;
    std::vector<Enemy> enemies;
    bool _changeMaps;
    Character _hero;
    SDL_Texture *_background;
    Timer time;
public:
    Map();
    void initConstants(SDL_Renderer *renderer);
    void loadMap1(SDL_Renderer *renderer);
    void showMap1(SDL_Renderer *renderer, float timeBetweenFrames);
    void loadMap2();
    void loadMap3();
    void reset();
};

#endif /* Map_hpp */

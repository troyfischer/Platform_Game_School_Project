#ifndef Map_hpp
#define Map_hpp

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <SDL.h>
#include "Platform.hpp"
#include "Enemy.hpp"
#include "Character.hpp"
#include "Item.hpp"
#include "Text.hpp"
#include "StartScreen.hpp"
#include "LoseScreen.hpp"
#include "WinScreen.hpp"

class Map
{
    /* All updates and map changes occur within the map class */
private:
    /*---------------Containers-------------------*/
    std::vector<Platform *> platforms;
    std::vector<Enemy *> enemies;
    std::vector<Item *> items;
    
    /*--------------Main Character-----------------*/
    Character _hero;
    
    /* Text that keeps the characters lives visible to the user */
    Text *_heroLivesText;
    
    /* Possible screens to render */
    StartScreen *_startScreen;
    LoseScreen *_loseScreen;
    WinScreen *_winScreen;
    
    /* Background of the map */
    SDL_Texture *_background;
    
    int currentMap; //holds the current map to be loaded and displayed

    bool _canCreateMap; //allows a map to be loaded
    bool _canShowMap; //allows a map to be shown
    bool _renderWin; //allows the WinScreen to be rendered
public:
    /*-------------Constructor/Destructor------------------*/
    Map();
    ~Map();
    
    /* Initializer */
    void init(SDL_Renderer *renderer);
    
    /* Methods to create desired map */
    void createMap1(SDL_Renderer *renderer);
    void createMap2(SDL_Renderer *renderer);
    void createMap3(SDL_Renderer *renderer);
    
    /* Method to create the map based on currentMap */
    void load(SDL_Renderer *renderer);
    
    /* Renders the map and handles all updates */
    void show(SDL_Renderer *renderer, float timeBetweenFrames);
    
    /* Empties all containers to create a new map */
    void reset();
    
    /* Renders start/lose/win screens if conditions are met */
    bool shouldShowStartScreen(SDL_Renderer *renderer, float timeBetweenFrames);
    bool shouldShowLoseScreen(SDL_Renderer *renderer);
    bool shouldShowWinScreen(SDL_Renderer *renderer);
};

#endif /* Map_hpp */

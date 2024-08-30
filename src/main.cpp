
/* **********This project does not own any of the images or sounds used in it************* */
/* All images and sounds were used for educational purposes as the project will not be distributed */

#include <stdio.h>
#include <vector>
#include "Character.hpp"
#include "Enemy.hpp"
#include "GameWindow.hpp"
#include "Sprite.hpp"
#include "Text.hpp"
#include "StartScreen.hpp"
#include "Platform.hpp"
#include "Map.hpp"
#include "LoseScreen.hpp"

int main(int argc, const char ** argv)
{
    GameWindow game("Dungeon Escape");
    
    Map map;
    map.init(game.getRenderer());

    float previousTick = 0.0f;
    float currentTick = 0.0f;
    float timeBetweenFrames = 0.0f; //will be in seconds
    SDL_Event e;
    
    /* Game loop */
    while (game.isOpen())
    {
        /* Calculating time between each frame */
        previousTick = currentTick;
        currentTick = SDL_GetTicks();
        timeBetweenFrames = (currentTick - previousTick) / 1000.0f;
        
        /* Event loop */
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                game.closeGameWindow();
            }
        }
        
        if (!map.shouldShowStartScreen(game.getRenderer(), timeBetweenFrames))
        {
            /* If the game has started load the map
             The method has checks within it to make sure it only happens once */
            
            map.load(game.getRenderer());
        }
        if (!map.shouldShowLoseScreen(game.getRenderer()) && !map.shouldShowWinScreen(game.getRenderer()))
        {
            /* if the game has started, the character's lives != 0
             and the current map != 4 then show the map */
            
            map.show(game.getRenderer(), timeBetweenFrames);
        }        
        
    }
    return 0;
}

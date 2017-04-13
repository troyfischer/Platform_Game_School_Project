#include <stdio.h>
#include "header.h"

int main(int argc, const char ** argv)
{
    GameWindow game("Dungeon Escape");
    
    StartScreen startScreen(game.getRenderer());
    
    Map map;
    map.initConstants(game.getRenderer());
    map.loadMap1(game.getRenderer());
    
    Enemy bad;
    bad.init(game.getRenderer(), "/Users/Troy/Documents/workspace/Xcode/Working/Platformer/Platformer/enemyspritesheet.png", 1, 1, false);
    bad.setPos(200, 200);

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
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                game.closeGameWindow();
            }
        }
        
        if (!startScreen.getStart())
        {
            startScreen.render(game.getRenderer(), timeBetweenFrames);
            SDL_RenderPresent(game.getRenderer());
            SDL_RenderClear(game.getRenderer());
        }
        else
        {
            map.showMap1(game.getRenderer(), timeBetweenFrames);
            bad.render(game.getRenderer(), timeBetweenFrames);
            SDL_RenderPresent(game.getRenderer());
            SDL_RenderClear(game.getRenderer());
            
        }
    }
    
    
    return 0;
}

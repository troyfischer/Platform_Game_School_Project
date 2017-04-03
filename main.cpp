#include <stdio.h>
#include "GameWindow.hpp"
#include "Character.hpp"

void handleAllEvents(GameWindow &gameWindow)
{
    
}

int main(int argc, const char ** argv)
{
    GameWindow gameWindow("Dungeon Escape");
    
    Character sprite(gameWindow.getRenderer(), 0, 0, 4, 4);
    
    float previousTick = 0.0f;
    float currentTick = 0.0f;
    float timeBetweenFrames = 0.0f; //will be in seconds
    SDL_Event e;
    while (gameWindow.isOpen())
    {
        previousTick = currentTick;
        currentTick = SDL_GetTicks();
        timeBetweenFrames = (currentTick - previousTick) / 1000.0f;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                gameWindow.closeGameWindow();
            }
        }
        
        sprite.renderCharacter(gameWindow.getRenderer(), timeBetweenFrames);
        SDL_RenderPresent(gameWindow.getRenderer());
        SDL_RenderClear(gameWindow.getRenderer());
    }
    
    
    return 0;
}

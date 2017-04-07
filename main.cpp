#include <stdio.h>
#include "header.h"

int main(int argc, const char ** argv)
{
    GameWindow gameWindow("Dungeon Escape");
    
    StartScreen startScreen(gameWindow.getRenderer());
    
    Sprite *mainCharacter = new Character(gameWindow.getRenderer(), "/Users/Troy/Documents/workspace/Xcode/Working/Platformer/Platformer/SpriteSheet.png", 4, 4);
    Sprite *enemy = new Enemy(gameWindow.getRenderer(), "/Users/Troy/Documents/workspace/Xcode/Working/Platformer/Platformer/enemyspritesheet.png", 1, 1, WINDOW_WIDTH/2, WINDOW_HEIGHT/2, false);
    
    
    float previousTick = 0.0f;
    float currentTick = 0.0f;
    float timeBetweenFrames = 0.0f; //will be in seconds
    SDL_Event e;
    
    /* Game loop */
    while (gameWindow.isOpen())
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
                gameWindow.closeGameWindow();
            }
        }
        
        if (!startScreen.getStart())
        {
            startScreen.render(gameWindow.getRenderer(), timeBetweenFrames);
            SDL_RenderPresent(gameWindow.getRenderer());
        }
        else
        {
            gameWindow.renderBackground();
            mainCharacter->render(gameWindow.getRenderer(), timeBetweenFrames);
            enemy->render(gameWindow.getRenderer(), timeBetweenFrames);
            SDL_RenderPresent(gameWindow.getRenderer());
            SDL_RenderClear(gameWindow.getRenderer());
        }
        gameWindow.regulateFrameRate(currentTick);
    }
    
    
    return 0;
}

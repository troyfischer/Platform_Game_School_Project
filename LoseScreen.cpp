#include "LoseScreen.hpp"

LoseScreen::LoseScreen(SDL_Renderer *renderer)
{
    _background = {0,0,WINDOW_WIDTH,WINDOW_HEIGHT};
    
    _youLost = new Text(renderer, "You didn't escape the dungeon", {255,0,0,255}, "/Users/Troy/Documents/workspace/Xcode/Working/Platformer/Platformer/Times New Roman.ttf", 30);
    _tryAgain = new Text(renderer, "Press Return to try again", {255,0,0,255}, "/Users/Troy/Documents/workspace/Xcode/Working/Platformer/Platformer/Times New Roman.ttf", 20);
}

LoseScreen::~LoseScreen()
{
}

bool LoseScreen::_playAgain()
{
    const Uint8 *keyState = SDL_GetKeyboardState(NULL);
    
    if (keyState[SDL_SCANCODE_RETURN])
    {
        return true;
    }
    return false;
}

void LoseScreen::render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &_background);
    _youLost->renderText(renderer, WINDOW_WIDTH/2 - 250, 100, 500, 200);
    _tryAgain->renderText(renderer, WINDOW_WIDTH/2 - 200, WINDOW_HEIGHT/2, 400, 200);
    
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
}

void LoseScreen::startNewGame(StartScreen **start, Character &hero)
{
    (*start)->canStart();
    hero.newGame();
}

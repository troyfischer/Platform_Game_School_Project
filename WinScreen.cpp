#include "WinScreen.hpp"

WinScreen::WinScreen(SDL_Renderer *renderer)
{
    _background = {0,0,WINDOW_WIDTH, WINDOW_HEIGHT};
    
    _youWon = new Text(renderer, "You escaped!",{0,255,255,255}, "./resources/Times New Roman.ttf", 30);
    _tryAgain = new Text(renderer, "Press Return to play again", {0,255,255,255}, "./resources/Times New Roman.ttf", 30);
}

WinScreen::~WinScreen()
{
}

bool WinScreen::_playAgain()
{
    const Uint8 *keyState = SDL_GetKeyboardState(NULL);
    
    if (keyState[SDL_SCANCODE_RETURN])
    {
        return true;
    }
    return false;
}

void WinScreen::render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &_background);
    
    _youWon->renderText(renderer, WINDOW_WIDTH/2 - 250, 100, 500, 200);
    _tryAgain->renderText(renderer, WINDOW_WIDTH/2 - 200, WINDOW_HEIGHT/2, 400, 200);
    
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
}

void WinScreen::startNewGame(StartScreen **start, Character &hero)
{
    (*start)->canStart();
    hero.newGame();
}

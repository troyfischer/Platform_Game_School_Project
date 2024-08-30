#ifndef LoseScreen_hpp
#define LoseScreen_hpp

#include <stdio.h>
#include "Text.hpp"
#include "GameWindow.hpp"
#include "StartScreen.hpp"
#include "Character.hpp"

class LoseScreen
{
    /* The class creates the screen that shows when the 
     character runs out of lives in the game */
private:
    SDL_Rect _background;
    Text *_youLost;
    Text *_tryAgain;
public:
    /*-------------Constructor/Destructor------------------*/
    LoseScreen(SDL_Renderer *renderer);
    ~LoseScreen();
    
    /*-----------------Render method-------------------*/
    void render(SDL_Renderer *renderer);
    
    /* Methods for starting a new game */
    bool _playAgain();
    void startNewGame(StartScreen **start, Character &hero);
};

#endif /* LoseScreen_hpp */

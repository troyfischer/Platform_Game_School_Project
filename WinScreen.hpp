#ifndef WinScreen_hpp
#define WinScreen_hpp

#include <stdio.h>
#include <SDL.h>
#include "Text.hpp"
#include "StartScreen.hpp"
#include "Character.hpp"

class WinScreen
{
    /* The class creates the screen that shows when the
     character current level reaches 4 */
private:
    SDL_Rect _background;
    Text *_youWon;
    Text *_tryAgain;
public:
    /*-------------Constructor/Destructor------------------*/
    WinScreen(SDL_Renderer *renderer);
    ~WinScreen();
    
    /* Gets current keystate */
    bool _playAgain();
    
    /* Display Method */
    void render(SDL_Renderer *renderer);
    
    /* Allows start screen to show again */
    void startNewGame(StartScreen **start, Character &hero);
};

#endif /* WinScreen_hpp */

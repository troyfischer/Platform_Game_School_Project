//
//  main.cpp
//  Platformer
//
//  Created by Troy Fischer on 3/25/17.
//  Copyright © 2017 Troy Fischer. All rights reserved.
//

#include <stdio.h>
#include "GameWindow.hpp"
#include "Character.hpp"

void handleAllEvents(GameWindow &gameWindow, Character &cartman)
{
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        gameWindow.handleWindowEvent(e);
        cartman.handleMovement(e);
    }
}

int main(int argc, const char ** argv)
{
    GameWindow gameWindow("Dungeon Escape");
    Character cartman(gameWindow, WINDOW_WIDTH/4, WINDOW_HEIGHT/4, 100, 100);
    
    while (gameWindow.isOpen()) {
        float start_tick = SDL_GetTicks();
        handleAllEvents(gameWindow, cartman);
        cartman.drawCharacter();
        gameWindow.renderBackground();
        gameWindow.regulateFrameRate(start_tick);
    }
    return 0;
}

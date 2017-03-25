//
//  Character.cpp
//  Platformer
//
//  Created by Troy Fischer on 3/25/17.
//  Copyright © 2017 Troy Fischer. All rights reserved.
//

#include "Character.hpp"

Character::Character(GameWindow &gameWindow, int x, int y, int w, int h) : GameWindow(gameWindow), _x(x), _y(y), _w(w), _h(h)
{
    charIMG = NULL;
}

Character::~Character()
{
    SDL_DestroyTexture(charIMG);
}

void Character::loadTexture(std::string path)
{
    charIMG = IMG_LoadTexture(GameWindow::_renderer, path.c_str());
    if (charIMG == NULL) {
        logIMGError("IMG_LoadTexture");
        GameWindow::_open = false;
    }
}

void Character::drawCharacter()
{
    charRect = {_x, _y, _w, _h};

    loadTexture("/Users/Troy/Documents/workspace/Xcode/Working/Platformer/Platformer/cartman.jpg");
    if (charIMG) {
        SDL_RenderCopy(GameWindow::_renderer, charIMG, NULL, &charRect);
    }
}

void Character::applyGravity()
{
    while (_y + _h <= WINDOW_HEIGHT) {
        _y += 1;
    }
}

void Character::jump()
{
    _y += 50;
}

void Character::handleMovement(SDL_Event &e)
{
        switch (e.type) {
            case SDL_KEYDOWN:
                if (e.key.keysym.sym == SDLK_w)
                {
                    //check to make sure it won't be off the screen
                    if (_y - 10 >= 0) {
                        _y -= 40;
                    }
                }
                else if (e.key.keysym.sym == SDLK_a)
                {
                    //check to make sure it won't be off the screen
                    if (_x - 10 >= 0) {
                        _x -= 10;
                    }
                }
                else if (e.key.keysym.sym == SDLK_s)
                {
                    //check to make sure it won't be off the screen
                    if (_y + _h + 10 <= WINDOW_HEIGHT) {
                        _y += 10;
                    }
                }
                else if (e.key.keysym.sym == SDLK_d)
                {
                    //check to make sure it won't be off the screen
                    if (_x + _w + 10 <= WINDOW_WIDTH) {
                        _x += 10;
                    }
                }
                break;
            default:
                break;
        }
    applyGravity();
}


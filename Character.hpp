//
//  Character.hpp
//  Platformer
//
//  Created by Troy Fischer on 3/25/17.
//  Copyright © 2017 Troy Fischer. All rights reserved.
//

#ifndef Character_hpp
#define Character_hpp

#include <stdio.h>
#include "GameWindow.hpp"

class Character : public GameWindow
{
    SDL_Texture *charIMG;
    SDL_Rect charRect;
    int _x;
    int _y;
    int _w;
    int _h;
    void loadTexture(std::string path);
public:
    Character(GameWindow &gameWindow, int x, int y, int w, int h);
    ~Character();
    void drawCharacter();
    void applyGravity();
    void jump();
    void handleMovement(SDL_Event &e);
};

#endif /* Character_hpp */

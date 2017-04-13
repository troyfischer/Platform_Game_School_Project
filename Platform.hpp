//
//  Platform.hpp
//  Platformer
//
//  Created by Troy Fischer on 4/12/17.
//  Copyright © 2017 Troy Fischer. All rights reserved.
//

#ifndef Platform_hpp
#define Platform_hpp

#include <stdio.h>
#include <SDL2/SDL.h>

class Platform
{
private:
    SDL_Rect _platform;
public:
    Platform();
    void setPlatform(int x, int y);
    void show(SDL_Renderer *renderer);
    
    int getX();
    int getY();
    int getW();
    int getH();
    
    
};

#endif /* Platform_hpp */

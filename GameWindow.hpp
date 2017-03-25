//
//  GameWindow.hpp
//  Platformer
//
//  Created by Troy Fischer on 3/25/17.
//  Copyright © 2017 Troy Fischer. All rights reserved.
//

#ifndef GameWindow_hpp
#define GameWindow_hpp

#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

class GameWindow
{
private:
    SDL_Window *_window;
    std::string _title;
protected:
    SDL_Renderer *_renderer;
    void logSDLError(const std::string &msg) const;
    void logIMGError(const std::string &msg) const;
    bool _open;
public:
    GameWindow(std::string title);
    ~GameWindow();
    bool isOpen();
    void handleWindowEvent(SDL_Event &e);
    void renderBackground();
    void regulateFrameRate(float start_tick);
};

#endif /* GameWindow_hpp */

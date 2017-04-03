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
#include <SDL2_ttf/SDL_ttf.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

class GameWindow
{
private:
    SDL_Window *_window;
    SDL_Renderer *_renderer;
    SDL_Texture *_background;
    SDL_Rect _backgroundRect;
    TTF_Font *_livesFont;
    SDL_Texture *_livesTexture;
    TTF_Font *_levelFont;
    TTF_Font *_timeFont;
    std::string _title;
    void loadTexture(const std::string path);
    bool _open;
    
public:
    GameWindow(std::string title);
    ~GameWindow();
    SDL_Renderer * getRenderer();
    
    static void logSDLError(const std::string &msg);
    static void logIMGError(const std::string &msg);
    static void logTTFError(const std::string &msg);
    
    bool isOpen();
    void closeGameWindow();
    void handleWindowEvent(SDL_Event &e);
    void renderBackground();
    void regulateFrameRate(float start_tick);
};

#endif /* GameWindow_hpp */

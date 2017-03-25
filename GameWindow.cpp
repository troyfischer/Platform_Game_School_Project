//
//  GameWindow.cpp
//  Platformer
//
//  Created by Troy Fischer on 3/25/17.
//  Copyright © 2017 Troy Fischer. All rights reserved.
//

#include "GameWindow.hpp"

GameWindow::GameWindow(std::string title) : _title(title)
{
    _window = NULL;
    _renderer = NULL;
    _open = true;
    
    //initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        logSDLError("SDL_Init");
        _open = false;
    }
    
    //initialize IMG
    int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        logIMGError("IMG_Init");
    }
    
    //create a window
    _window = SDL_CreateWindow(_title.c_str(),
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               WINDOW_WIDTH,
                               WINDOW_HEIGHT,
                               SDL_WINDOW_SHOWN);
    if (_window == NULL)
    {
        logSDLError("SDL_CreateWindow");
        _open = false;
    }
    
    //create a renderer
    _renderer = SDL_CreateRenderer(_window,
                                   -1,
                                   SDL_RENDERER_ACCELERATED);
    if (_renderer == NULL)
    {
        logSDLError("SDL_CreateRenderer");
        _open = false;
    }
    
}

GameWindow::~GameWindow()
{
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_renderer);
    SDL_Quit();
}

bool GameWindow::isOpen()
{
    return _open;
}

void GameWindow::handleWindowEvent(SDL_Event &e)
{
        switch (e.type) {
            case SDL_QUIT:
                _open = false;
                break;
            case SDL_KEYDOWN:
                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    _open = false;
                }
                break;
            default:
                break;
        }
}

void GameWindow::renderBackground()
{
    SDL_RenderPresent(_renderer);
    
    if (SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255) < 0)
    {
        logSDLError("SDL_SetRenderDrawColor");
        _open = false;
    }
    if (SDL_RenderClear(_renderer) < 0) {
        logSDLError("SDL_RenderClear");
        _open = false;
    }
    
}

void GameWindow::regulateFrameRate(float start_tick)
{
    float fps = 60.0;
    float one_second = 1000;
    
    if ((one_second / fps) > (SDL_GetTicks() - start_tick)) {
        SDL_Delay((one_second / fps) - (SDL_GetTicks() - start_tick));
    }
}

//private member functions

void GameWindow::logSDLError(const std::string &msg) const
{
    std::cerr << msg << " error: " << SDL_GetError() << std::endl;
}

void GameWindow::logIMGError(const std::string &msg) const
{
    std::cerr << msg << " error: " << IMG_GetError() << std::endl;
}

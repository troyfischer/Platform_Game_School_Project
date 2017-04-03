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
    _background = NULL;
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
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        logIMGError("IMG_Init");
        _open = false;
    }
    
    //initialize TTF
    if (TTF_Init() == -1)
    {
        logTTFError("TTF_Init()");
        _open = false;
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
                                   SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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
    SDL_DestroyTexture(_background);
    SDL_Quit();
    
    TTF_Quit();
    
    IMG_Quit();
}

SDL_Renderer * GameWindow::getRenderer()
{
    return _renderer;
}

bool GameWindow::isOpen()
{
    return _open;
}

void GameWindow::closeGameWindow()
{
    _open = false;
}

void GameWindow::handleWindowEvent(SDL_Event &e)
{
        switch (e.type)
        {
            case SDL_QUIT:
                _open = false;
                break;
            case SDL_KEYDOWN:
                if (e.key.keysym.sym == SDLK_ESCAPE)
                {
                    _open = false;
                }
                break;
            default:
                break;
        }
}

void GameWindow::renderBackground()
{
    _background = IMG_LoadTexture(_renderer, "/Users/Troy/Documents/workspace/Xcode/Working/Platformer/Platformer/background.jpg");
    SDL_RenderCopy(_renderer, _background, NULL, NULL);
    //_backgroundRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
    //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    //SDL_RenderClear(renderer);
    //SDL_RenderFillRect(renderer, &_backgroundRect);
}

void GameWindow::regulateFrameRate(float start_tick)
{
    float fps = 60.0f;
    float one_second = 1000.0f;
    
    if ((one_second / fps) > (SDL_GetTicks() - start_tick))
    {
        SDL_Delay((one_second / fps) - (SDL_GetTicks() - start_tick));
    }
}

//private member functions

void GameWindow::logSDLError(const std::string &msg)
{
    std::cerr << msg << " error: " << SDL_GetError() << std::endl;
}

void GameWindow::logIMGError(const std::string &msg)
{
    std::cerr << msg << " error: " << IMG_GetError() << std::endl;
}

void GameWindow::logTTFError(const std::string &msg)
{
    std::cerr << msg << " error: " << TTF_GetError() << std::endl;
}

void GameWindow::loadTexture(const std::string path)
{
    _backgroundRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
    _background = IMG_LoadTexture(_renderer, path.c_str());
    SDL_RenderCopy(_renderer, _background, NULL, &_backgroundRect);
}

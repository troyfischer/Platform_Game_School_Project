#include "GameWindow.hpp"

GameWindow::GameWindow(std::string title)
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
    
    //Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        _open = false;
    }
    
    
    //create a window
    _window = SDL_CreateWindow(title.c_str(),
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
    //Quit all subsystems
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_renderer);
    SDL_Quit();
    
    TTF_Quit();
    
    IMG_Quit();
    
    Mix_Quit();
}

void GameWindow::logSDLError(const std::string &msg)
{ std::cerr << msg << " error: " << SDL_GetError() << std::endl; }

void GameWindow::logIMGError(const std::string &msg)
{ std::cerr << msg << " error: " << IMG_GetError() << std::endl; }

void GameWindow::logTTFError(const std::string &msg)
{ std::cerr << msg << " error: " << TTF_GetError() << std::endl; }

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

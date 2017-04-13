#ifndef GameWindow_hpp
#define GameWindow_hpp

#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 640

class GameWindow
{
private:
    SDL_Window *_window;
    SDL_Renderer *_renderer;
    SDL_Texture *_background;
    SDL_Rect _backgroundRect;
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
    void renderBackground();
    void regulateFrameRate(float start_tick);
};

#endif /* GameWindow_hpp */

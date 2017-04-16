#ifndef GameWindow_hpp
#define GameWindow_hpp

#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 650

class GameWindow
{
    /* The class is responsible for the opening and closing of the window
     and stores the renderer used throughout the project */
    
    /* The frame rate is regulated through vsync which is why there is no
     method to manually regulate the frame rate */
private:
    /*------------------SDL_Fields------------------*/
    SDL_Window *_window;
    SDL_Renderer *_renderer;
    
    /* Holds the open status of the window */
    bool _open;
    
public:
    /*-------------Constructor/Destructor------------------*/
    GameWindow(std::string title);
    ~GameWindow();
    
    /*-----------------Error Loggging--------------------*/
    static void logSDLError(const std::string &msg);
    static void logIMGError(const std::string &msg);
    static void logTTFError(const std::string &msg);
    
    /*--------------Setters and Getters--------------------*/
    SDL_Renderer * getRenderer();
    bool isOpen();
    void closeGameWindow();
};

#endif /* GameWindow_hpp */

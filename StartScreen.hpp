#ifndef StartScreen_hpp
#define StartScreen_hpp

#include <stdio.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "Text.hpp"
#include "GameWindow.hpp"

class StartScreen
{
private:
    bool _start;//determines whether the StartScreen should be shown
    
    /*------------------SDL Fields---------------*/
    SDL_Rect _background;
    SDL_Texture *_sprite;
    SDL_Rect _cropRect;
    SDL_Rect _spriteRect;
    
    /* For cropping and displaying the sprite texture */
    float _spriteWidth;
    float _textureWidth;
    
    /*--------------Regulates animation----------------*/
    float _frameCount;
    
    /* All text to be displayed on the screen */
    Text *_title;
    Text *_controls;
    Text *_W;
    Text *_D;
    Text *_A;
    Text *_pressSpaceText;
    
    /* Animation */
    void animate(float timeBetweenFrames);
    
    /* Gets current key pressed */
    void startGame();
public:
    /*--------------Setters and Getters--------------------*/
    StartScreen(SDL_Renderer *renderer);
    ~StartScreen();
    
    /*------------------Display--------------*/
    void render(SDL_Renderer *renderer, float timeBetweenFrames);
    
    /*----------------Setters and Getters--------------------*/
    bool getStart();
    void canStart();
};

#endif /* StartScreen_hpp */

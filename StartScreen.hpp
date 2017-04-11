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
    bool _start;
    SDL_Rect _background;
    SDL_Texture *_sprite;
    SDL_Rect _cropRect;
    SDL_Rect _spriteRect;
    SDL_Texture *_wizard;
    SDL_Rect _enemyCropRect;
    SDL_Rect _enemyRect;
    
    float _spriteWidth;
    float _textureWidth;
    float _frameCount;
    
    Text *_title;
    Text *_controls;
    Text *_W;
    Text *_D;
    Text *_A;
    Text *_pressSpaceText;
    
    void startGame();
public:
    StartScreen(SDL_Renderer *renderer);
    void animate(float timeBetweenFrames);
    void render(SDL_Renderer *renderer, float timeBetweenFrames);
    bool getStart();
};

#endif /* StartScreen_hpp */

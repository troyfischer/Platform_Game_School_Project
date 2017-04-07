#include "StartScreen.hpp"

StartScreen::StartScreen(SDL_Renderer *renderer)
{
    /* Initialization */
    _sprite = NULL;
    _title = NULL;
    _controls = NULL;
    _W = NULL;
    _D = NULL;
    _A = NULL;
    _pressSpaceText = NULL;
    _start = false;
    
    /* Initialize sprite */
    SDL_Surface *tempSurface = NULL;
    tempSurface = IMG_Load("/Users/Troy/Documents/workspace/Xcode/Working/Platformer/Platformer/SpriteSheet.png");
    if (!tempSurface)
    {
        printf("IMG_Load error: %s\n", IMG_GetError());
    }
    else
    {
        _sprite = SDL_CreateTextureFromSurface(renderer, tempSurface);
        if (!_sprite)
        {
            printf("SDL_CreateTextureFromSurface error: %s\n", SDL_GetError());
        }
        else
        {
            SDL_QueryTexture(_sprite, NULL, NULL, &_cropRect.w, &_cropRect.h);
        }
        SDL_FreeSurface(tempSurface);
    }
    
    _textureWidth = _cropRect.w;
    _cropRect.w /= 4;
    _cropRect.h /= 4;
    _cropRect.x = 0;
    _cropRect.y = 0;
    _spriteWidth = _cropRect.w;
    
    _spriteRect.w = 100;
    _spriteRect.h = 100;
    _spriteRect.x = WINDOW_WIDTH - _spriteRect.w - 75;
    _spriteRect.y = 50;
    
    _frameCount = 0;
    
    /* Initialize text */
    _title = new Text(renderer, "Dungeon Escape", {255,0,0,255}, "/Users/Troy/Documents/workspace/Xcode/Working/Platformer/Platformer/Times New Roman.ttf", 20);
    _controls = new Text(renderer, "Controls", {255,0,0,255}, "/Users/Troy/Documents/workspace/Xcode/Working/Platformer/Platformer/Times New Roman.ttf", 20);
    _W = new Text(renderer, "W - Jump", {255,0,0,255}, "/Users/Troy/Documents/workspace/Xcode/Working/Platformer/Platformer/Times New Roman.ttf", 15);
    _D = new Text(renderer, "D - Move Right", {255,0,0,255}, "/Users/Troy/Documents/workspace/Xcode/Working/Platformer/Platformer/Times New Roman.ttf", 20);
    _A = new Text(renderer, "A - Move Left", {255,0,0,255}, "/Users/Troy/Documents/workspace/Xcode/Working/Platformer/Platformer/Times New Roman.ttf", 20);
    _pressSpaceText = new Text(renderer, "Press Space to begin", {255,0,0,255}, "/Users/Troy/Documents/workspace/Xcode/Working/Platformer/Platformer/Times New Roman.ttf", 20);
    
}

void StartScreen::startGame()
{
    const Uint8 *keyState = SDL_GetKeyboardState(NULL);
    
    if (keyState[SDL_SCANCODE_SPACE])
    {
        _start = true;
    }
}

void StartScreen::animate(float timeBetweenFrames)
{
    _frameCount += timeBetweenFrames;
    if (_frameCount >= 0.2f)
    {
        _frameCount = 0;
        _cropRect.x += _spriteWidth;
        if (_cropRect.x >= _textureWidth)
        {
            _cropRect.x = 0;
        }
    }
}

void StartScreen::render(SDL_Renderer *renderer, float timeBetweenFrames)
{
    startGame();
    _background = {0,0,WINDOW_WIDTH,WINDOW_HEIGHT};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &_background);
    int w = 150;
    int h = 30;
    _title->renderText(renderer, WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT - 350, 300, 200);
    _controls->renderText(renderer, 10, 0, w, 50);
    _W->renderText(renderer, 10, 50, w, h);
    _D->renderText(renderer, 10, 50+h, w, h);
    _A->renderText(renderer, 10, 50+2*h, w, h);
    _pressSpaceText->renderText(renderer, WINDOW_WIDTH/2 - 150, WINDOW_HEIGHT - 150, 300, 150);
    animate(timeBetweenFrames);
    SDL_RenderCopy(renderer, _sprite, &_cropRect, &_spriteRect);
}

bool StartScreen::getStart()
{
    return _start;
}

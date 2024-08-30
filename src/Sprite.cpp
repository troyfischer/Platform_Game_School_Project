#include "Sprite.hpp"
#include "GameWindow.hpp"

Sprite::Sprite()
{
}

Sprite::~Sprite()
{
    SDL_DestroyTexture(_spriteTexture);
    _spriteTexture = NULL;
}

void Sprite::initSprite(SDL_Renderer *renderer, std::string textureFilePath, int numFramesX, int numFramesY)
{
    _spriteTexture = NULL;
    _textureSurface = NULL;
    
    /* Using IMG_Load which returns an SDL_Surface pointer */
    _textureSurface = IMG_Load(textureFilePath.c_str());
    if (!_textureSurface)
    {
        logIMG_Error("IMG_Load");
    }
    else
    {
        /* Use the loaded surface to create a texture for the renderer */
        _spriteTexture = SDL_CreateTextureFromSurface(renderer, _textureSurface);
    }
    
    if (!_spriteTexture)
    {
        logSDL_Error("SDL_CreateTextureFromSurface");
    }
    else
    {
        SDL_QueryTexture(_spriteTexture, NULL, NULL, &_cropRect.w, &_cropRect.h); //the total width and height of the png/jpg file is important for separating it into individual frames
        SDL_FreeSurface(_textureSurface); //frees the SDL_Surface
    }
    
    /* These variables will store the total width and height as _cropRect.w and _cropRect.h need to change */
    _textureWidth = _cropRect.w;
    _textureHeight = _cropRect.h;
    
    _cropRect.w /= numFramesX;
    _cropRect.h /= numFramesY;
    
    /* These variables will store the width and height of each individual frame on the sprite sheet */
    _spriteWidth = _cropRect.w;
    _spriteHeight = _cropRect.h;
    
    /* Start the _cropRect to the top leftmost sprite frame */
    _cropRect.x = 0;
    _cropRect.y = 0;
    
    /* The starting position will be set in the respective Character, Enemy or Item class */
}

bool Sprite::offScreen_y(bool up, float speed, float timeBetweenFrames)
{
    /* if up is true the check is for going off the top of the screen
     if up is false the check is for going off the bottom of the screen */
    
    if (up)
    {
        return _y + (-speed * timeBetweenFrames) <= 0;
    }
    else
    {
        return (_y + _spriteRect.h) + (speed * timeBetweenFrames) >= WINDOW_HEIGHT;
    }
}

bool Sprite::offScreen_x(bool right, float speed, float timeBetweenFrames)
{
    /* if right is true the check is for going off the right side of the screen
     if right is false the check is for going off the left side of the screen */
    
    if (right)
    {
        //right side
        return (_x + _spriteRect.w) + (speed * timeBetweenFrames) >= WINDOW_WIDTH;
    }
    else
    {
        //left side
        return _x + (-speed * timeBetweenFrames) <= 0;
    }
}

void Sprite::logSDL_Error(const std::string &msg)
{ std::cerr << msg << " error: " << SDL_GetError() << std::endl; }

void Sprite::logIMG_Error(const std::string &msg)
{ std::cerr << msg << " error: " << IMG_GetError() << std::endl; }

void Sprite::logTTF_Error(const std::string &msg)
{ std::cerr << msg << " error: " << TTF_GetError() << std::endl; }

void Sprite::render(SDL_Renderer *renderer)
{ SDL_RenderCopy(renderer, _spriteTexture, &_cropRect, &_spriteRect); }

//Setters and Getters
float Sprite::get_radius() { return _spriteRect.w/2.0f; }
float Sprite::get_x_Origin() { return _x + get_radius(); }
float Sprite::get_y_Origin() { return  _y + get_radius(); }
int Sprite::getSpriteHeight() { return  _spriteRect.h; }
int Sprite::getSpriteWidth() { return  _spriteRect.w; }

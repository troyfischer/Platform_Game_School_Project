#ifndef Sprite_hpp
#define Sprite_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

//Base class for Character, Enemy and Item
class Sprite
{
    friend class Enemy;
    friend class Character;
    
private:
    /* ----------------------SDL fields----------------------------- */
    SDL_Rect _spriteRect;
    SDL_Rect _cropRect;
    SDL_Texture *_spriteTexture;
    SDL_Surface *_textureSurface;
    
    /* -----------------Sprite Sheet cropping fields------------------ */
    float _spriteWidth;
    float _spriteHeight;
    float _textureWidth;
    float _textureHeight;
    
    /* ----------------------Position fields------------------------- */
    float _x, _y; //to handle movement more fluidly
    float _x_Origin, _y_Origin; //for circular based collisions
    float _radius; //for circular based collisions
    
    /* ---------------------Attribute fields--------------------------- */
    float _groundMoveSpeed; //move speed
    
    /* --------------------Private methods------------------------------ */
    bool offScreen_y(bool up, float speed, float timeBetweenFrames);
    bool offScreen_x(bool right, float speed, float timeBetweenFrames);
    virtual void update(float timeBetweenFrames) = 0; //each friend class will update differently
    
    /* -----------------Error logging funcitons------------------------- */
    void logSDL_Error(const std::string &msg);
    void logIMG_Error(const std::string &msg);
    void logTTF_Error(const std::string &msg);

    /* Private constructor to keep Sprite from constructing itself */
    Sprite(SDL_Renderer *renderer, std::string textureFilePath, int numFramesX, int numFramesY);

public:
    ~Sprite();
    /* -----------------Collision necessary methods------------------------- */
    float get_x_Origin();
    float get_y_Origin();
    float get_radius();
    
    /* -------------------Display method------------------------------------- */
    virtual void render(SDL_Renderer *renderer, float timeBetweenFrames) = 0; //each friend class will have it's own render method
};

#endif /* Sprite_hpp */

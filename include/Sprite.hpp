
#ifndef Sprite_hpp
#define Sprite_hpp

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <stdio.h>
#include <string>

// Base class for Character, Enemy and Item
class Sprite {
  friend class Enemy;
  friend class Character;
  friend class Item;

private:
  /* ----------------------SDL fields----------------------------- */
  SDL_Rect _spriteRect;
  SDL_Rect _cropRect;
  SDL_Texture *_spriteTexture;
  SDL_Surface *_textureSurface;

  /* -----------------Sprite Sheet cropping fields------------------ */
  int _spriteWidth;
  int _spriteHeight;
  int _textureWidth;
  int _textureHeight;

  /* ----------------------Position fields------------------------- */
  float _x, _y; // to handle movement more fluidly

  /* ---------------------Attribute fields--------------------------- */
  float _xVel; // x move speed
  float _yVel; // y move speed

  /* Checks to ensure the sprite stays within the bounds of the screen */
  bool offScreen_y(bool up, float speed, float timeBetweenFrames);
  bool offScreen_x(bool right, float speed, float timeBetweenFrames);

  /* -----------------Error logging funcitons------------------------- */
  void logSDL_Error(const std::string &msg);
  void logIMG_Error(const std::string &msg);
  void logTTF_Error(const std::string &msg);

  /* Private constructor to keep Sprite from constructing itself */
  Sprite();

public:
  /* Destructor */
  ~Sprite();

  /* Initialization */
  void initSprite(SDL_Renderer *renderer, std::string textureFilePath,
                  int numFramesX, int numFramesY);

  /* ----------------------Display method-------------------------------------
   */
  void render(SDL_Renderer *renderer); // each friend class will have it's own
                                       // render method

  /*-----------------Setters and Getters--------------------*/
  float get_x_Origin();
  float get_y_Origin();
  float get_radius();
  int getSpriteHeight();
  int getSpriteWidth();
};

#endif /* Sprite_hpp */

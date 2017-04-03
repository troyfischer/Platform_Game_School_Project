#ifndef Character_hpp
#define Character_hpp

#include <stdio.h>
#include "GameWindow.hpp"


class Character
{
    SDL_Texture *_texture;
    SDL_Rect _cropRect;
    SDL_Rect _playerRect;
    float _moveSpeed;
    float _frameCounter;
    int _spriteWidth, _spriteHeight;
    int _textureWidth, _textureHeight;
    float _x, _y;
    bool _isMoving;
    void update(float deltaT);
    void drawCharacter(SDL_Renderer *renderer);
public:
    Character(SDL_Renderer *renderer, int x, int y, int framesX, int framesY);
    ~Character();
    void renderCharacter(SDL_Renderer *renderer, float deltaT);
};

#endif /* Character_hpp */

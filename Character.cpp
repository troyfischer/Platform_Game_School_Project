//
//  Character.cpp
//  Platformer
//
//  Created by Troy Fischer on 3/25/17.
//  Copyright © 2017 Troy Fischer. All rights reserved.
//

#include "Character.hpp"
#include "GameWindow.hpp"

Character::Character(SDL_Renderer *renderer, int x, int y, int numSpritesX, int numSpritesY)
{
    _texture = NULL;
    _moveSpeed = 100.0f; //default movespeed
    
    SDL_Surface *charSurface = NULL;
    charSurface = IMG_Load("/Users/Troy/Documents/workspace/Xcode/Working/Platformer/Platformer/SpriteSheet.png");
    
    if (!charSurface)
    {
        GameWindow::logIMGError("IMG_Load");
    }
    else
    {
        _texture = SDL_CreateTextureFromSurface(renderer, charSurface);
        if (!_texture)
        {
            GameWindow::logSDLError("SDL_CreateTextureFromSurface");
        }
    }
    
    SDL_FreeSurface(charSurface);
    
    SDL_QueryTexture(_texture, NULL, NULL, &_cropRect.w, &_cropRect.h);
        
    /* The _cropRect is going to take the individual sprite off of the sprite sheet
     The _cropRect size is going to be determined by how many sprite frames there are in each row and column
     The _cropRect is then going to be fit into the _playerRect */
    
    //Sets the starting position of the character
    _x = x;
    _y = y;
    
    //_textureWidth holds the total width of the sprite sheet & _textureHeight holds the height of the sprite sheet
    _textureWidth = _cropRect.w;
    _textureHeight = _cropRect.h;
    
    //sets the _cropRect to be the size of an individual sprite on the sheet
    _cropRect.w /= numSpritesX;
    _cropRect.h /= numSpritesY;
    
    //sets the size of each individual sprite
    _spriteWidth = _cropRect.w;
    _spriteHeight = _cropRect.h;
    
    //sets the size of the character on the screen
    _playerRect.w = 50;
    _playerRect.h = 50;
    
    _cropRect.x = 0;
    _cropRect.y = 0;
    
    _frameCounter = 0;
    
    _isMoving = false;
}

Character::~Character()
{
    SDL_DestroyTexture(_texture);
}

void Character::update(float deltaT)
{
    const Uint8 * keyStates = SDL_GetKeyboardState(NULL);
    
    _isMoving = true;
    
    if (keyStates[SDL_SCANCODE_W])
    {
        if (_y - (_moveSpeed * deltaT) >= 0)
        {
            _y -= _moveSpeed * deltaT;
        }
        _playerRect.y = _y;
    
        _cropRect.y = _spriteHeight * 3;
    }
    else if (keyStates[SDL_SCANCODE_S])
    {
        if ((_y + _playerRect.h) + (_moveSpeed * deltaT) <= WINDOW_HEIGHT)
        {
            _y += _moveSpeed * deltaT;
        }
        _playerRect.y = _y;
        
        _cropRect.y = 0;
    }
    else if (keyStates[SDL_SCANCODE_A])
    {
        if (_x - (_moveSpeed * deltaT) >= 0)
        {
            _x -= _moveSpeed * deltaT;
        }
        _playerRect.x = _x;
        
        _cropRect.y = _spriteHeight * 2;
    }
    else if (keyStates[SDL_SCANCODE_D])
    {
        if ((_x + _playerRect.w) + _moveSpeed * deltaT <= WINDOW_WIDTH)
        {
            _x += _moveSpeed * deltaT;
        }
        _playerRect.x = _x;
        
        _cropRect.y = _spriteHeight;
    }
    else
    {
        _isMoving = false;
    }
    
    if (_isMoving)
    {
        _frameCounter += deltaT;
        if (_frameCounter >= 0.15f)
        {
            _frameCounter = 0;
            _cropRect.x += _spriteWidth;
            if (_cropRect.x >= _textureWidth)
            {
                _cropRect.x = 0;
            }
        }
    }
    else
    {
        _frameCounter = 0;
        if (_cropRect.y == _spriteHeight * 2)
        {
            _cropRect.x = _textureWidth -_spriteWidth * 2;
        }
        else
        {
            _cropRect.x = _textureWidth - _spriteWidth;
        }
        
    }
}

void Character::drawCharacter(SDL_Renderer *renderer)
{
    SDL_RenderCopy(renderer, _texture, &_cropRect, &_playerRect);
}

void Character::renderCharacter(SDL_Renderer *renderer, float deltaT)
{
    update(deltaT);
    drawCharacter(renderer);
}

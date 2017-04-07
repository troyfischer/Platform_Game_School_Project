#include "Character.hpp"
#include <sstream>

Character::Character(SDL_Renderer *renderer, std::string textureFilePath, int numFramesX, int numFramesY) : Sprite(renderer, textureFilePath, numFramesX, numFramesY)
{
    /* Setting the size of the main character */
    _spriteRect.w = _spriteRect.h = 50;
    
    /* Setting intital position of main character */
    _x = _spriteRect.x = 0;
    _y = _spriteRect.y = WINDOW_HEIGHT - _spriteRect.h;
    
    
    /* Setting attributes */
    _lives = 3;
    _groundMoveSpeed = 100.0f;
    _inAirSpeed = 10.0f;
    _gravity = 0.0f;
    _jumpSpeed = -200.0f;
    _onGround = true;
    _isJumping = false;
    
    /* This portion will initialize the text on the screen that keeps the Character's lives */
    _livesText = NULL;
    std::stringstream textStream;
    textStream << "Lives: " << _lives;
    _livesText = new Text(renderer, textStream.str(), {0, 255, 255, 255},"/Users/Troy/Documents/workspace/Xcode/Working/Platformer/Platformer/Times New Roman.ttf", 20);
    
    _frameCount = 0;
}

const Uint8 * Character::getKeyState()
{
    const Uint8 *keyState = SDL_GetKeyboardState(NULL);
    
    return keyState;
}

void Character::jump(float timeBetweenFrames)
{

    const Uint8 *keyState = getKeyState();
    
    if (keyState[SDL_SCANCODE_W] && keyState[SDL_SCANCODE_D] && _isJumping)
    {
        animateInAir(keyState, timeBetweenFrames);
        _y += _jumpSpeed * timeBetweenFrames;
        _jumpSpeed += 2.0f;
        _spriteRect.y = _y;
        if (!offScreen_x(true, _groundMoveSpeed, timeBetweenFrames))
        {
            _x += _inAirSpeed * timeBetweenFrames;
            _spriteRect.x = _x;
        }
    }
    else if (keyState[SDL_SCANCODE_W] && keyState[SDL_SCANCODE_A] && _isJumping)
    {
        animateInAir(keyState, timeBetweenFrames);
        _y += _jumpSpeed * timeBetweenFrames;
        _jumpSpeed += 2.0f;
        _spriteRect.y = _y;
        if (!offScreen_x(false, _groundMoveSpeed, timeBetweenFrames))
        {
            _x += -_inAirSpeed * timeBetweenFrames;
            _spriteRect.x = _x;
        }
    }
    else if (keyState[SDL_SCANCODE_W] && _isJumping)
    {
        _y += _jumpSpeed * timeBetweenFrames;
        _jumpSpeed += 2.0f;
        _spriteRect.y = _y;
    }
    else
    {
        _isJumping = false;
    }
    
}

void Character::applyGravity(float timeBetweenFrames)
{
    const Uint8 *keyState = getKeyState();
    
    if (keyState[SDL_SCANCODE_D])
    {
        animateInAir(keyState, timeBetweenFrames);
        if (!offScreen_x(true, _groundMoveSpeed, timeBetweenFrames))
        {
            _x += _inAirSpeed * timeBetweenFrames;
            _spriteRect.x = _x;
        }
    }
    else if (keyState[SDL_SCANCODE_A])
    {
        animateInAir(keyState, timeBetweenFrames);
        if (!offScreen_x(false, _groundMoveSpeed, timeBetweenFrames))
        {
            _x += -_inAirSpeed * timeBetweenFrames;
            _spriteRect.x = _x;
        }
    }
    
    if (_isJumping && !offScreen_y(false, _gravity, timeBetweenFrames))
    {
        _y += _gravity * timeBetweenFrames;
        _spriteRect.y = _y;
        _gravity += 2.0f;
    }
    else if (!offScreen_y(false, _gravity, timeBetweenFrames))
    {
        _y += _gravity * timeBetweenFrames;
        _spriteRect.y = _y;
        _gravity += 1.0f;
    }
    else
    {
        resetJumpFields();
    }
}

void Character::resetJumpFields()
{
    _jumpSpeed = -200.0f;
    _onGround = true;
    _gravity = 0.0f;
}

void Character::animateInAir(const Uint8 *keyState, float timeBetweenFrames)
{
    if ((keyState[SDL_SCANCODE_W] && keyState[SDL_SCANCODE_D]) || keyState[SDL_SCANCODE_D])
    {
        _cropRect.y = _spriteHeight;
        _cropRect.x = 0;
    }
    else if ((keyState[SDL_SCANCODE_W] && keyState[SDL_SCANCODE_A]) || keyState[SDL_SCANCODE_A])
    {
        _cropRect.y = _spriteHeight * 2;
        _cropRect.x = _spriteWidth;
    }
    else
    {
        _cropRect.y = 0;
        _cropRect.x = _spriteWidth;
    }
}

void Character::animateRunning(const Uint8 *keyState, bool isMoving, float timeBetweenFrames)
{
    _cropRect.h = _spriteHeight; //for cropping issues
    
    if (keyState[SDL_SCANCODE_A])
    {
        //leftward animation
        _cropRect.y = _spriteHeight * 2;
    }
    else if (keyState[SDL_SCANCODE_D])
    {
        //rightward animation
        _cropRect.y = _spriteHeight;
    }
    
    if (isMoving)
    {
        _frameCount += timeBetweenFrames;
        if (_frameCount >= 0.15)
        {
            _frameCount = 0;
            _cropRect.x += _spriteWidth;
            if (_cropRect.x >= _textureWidth)
            {
                _cropRect.x = 0;
            }
        }
    }
    else
    {
        _frameCount = 0;
        
        /* The leftward moving standstill frame is in the first column of the sprite sheet
         while the rest of the standstill frames can be found in the second column of the 
         sprite sheet */
        
        if (_cropRect.y == _spriteHeight * 2)
        {
            _cropRect.x = 0;
        }
        else if (_cropRect.y == 0)
        {
            /* Fixes the cropping issues in the downward frames */
            _cropRect.x = _spriteWidth;
            _cropRect.h -= 20;
        }
        else
        {
            _cropRect.x = _spriteWidth;
        }
    }

}

void Character::update(float timeBetweenFrames)
{
    bool isMoving = true;
    
    const Uint8 *keyState = getKeyState();
    
    if (keyState[SDL_SCANCODE_W] && _onGround)
    {
        //jump
        _onGround = false;
        _isJumping = true;
    }
    else if (keyState[SDL_SCANCODE_A])
    {
        //leftward movement
        if (!offScreen_x(false, _groundMoveSpeed, timeBetweenFrames))
        {
            _x += -_groundMoveSpeed * timeBetweenFrames;
            _spriteRect.x = _x;
        }
        animateRunning(keyState, isMoving, timeBetweenFrames);
    }
    else if (keyState[SDL_SCANCODE_D])
    {
        //rightward movement
        if (!offScreen_x(true, _groundMoveSpeed, timeBetweenFrames))
        {
            _x : _x += _groundMoveSpeed * timeBetweenFrames;
            _spriteRect.x = _x;
        }
        animateRunning(keyState, isMoving, timeBetweenFrames);
    }
    else
    {
        isMoving = false;
        animateRunning(keyState, isMoving, timeBetweenFrames);
    }
    
    if (!_onGround)
    {
        jump(timeBetweenFrames);
        applyGravity(timeBetweenFrames);
    }
}

void Character::render(SDL_Renderer *renderer, float timeBetweenFrames)
{
    update(timeBetweenFrames);
    SDL_RenderCopy(renderer, _spriteTexture, &_cropRect, &_spriteRect);
    _livesText->renderText(renderer, 0, 0, 50, 50);
}

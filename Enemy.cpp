#include "Enemy.hpp"
#include "GameWindow.hpp"


Enemy::Enemy(SDL_Renderer *renderer, std::string textureFilePath, int numFramesX, int numFramesY, int startXpos, int startYpos, bool moveVertically) : Sprite(renderer, textureFilePath, numFramesX, numFramesY), _moveVertically(moveVertically)
{
    _spriteRect.w = _spriteRect.h = 50;
    _x = _spriteRect.x = startXpos;
    _y = _spriteRect.y = startYpos;
    
    _maxMoveDistance = 100.0f;
    _distanceMoved = 0.0f;
    _groundMoveSpeed = 100.0f;
}

void Enemy::moveVertically(float timeBetweenFrames)
{
    static bool up = true;
    
    if (up)
    {
        if (!offScreen_y(up, _groundMoveSpeed, timeBetweenFrames) && _distanceMoved <= _maxMoveDistance)
        {
            _distanceMoved += _groundMoveSpeed * timeBetweenFrames;
            _y += -_groundMoveSpeed * timeBetweenFrames;
            _spriteRect.y = _y;
        }
        else
        {
            up = false;
            _distanceMoved = 0;
        }
    }
    else if (!up)
    {
        if (!offScreen_y(false, _groundMoveSpeed, timeBetweenFrames) && _distanceMoved <= _maxMoveDistance)
        {
            _distanceMoved += _groundMoveSpeed * timeBetweenFrames;
            _y += _groundMoveSpeed * timeBetweenFrames;
            _spriteRect.y = _y;
        }
        else
        {
            up = true;
            _distanceMoved = 0;
        }
        
    }
}

void Enemy::moveHorizontally(float timeBetweenFrames)
{
    static bool right = true;
    
    if (right)
    {
        if (!offScreen_x(right, _groundMoveSpeed, timeBetweenFrames) && _distanceMoved <= _maxMoveDistance)
        {
            _distanceMoved += _groundMoveSpeed * timeBetweenFrames;
            _x += -_groundMoveSpeed * timeBetweenFrames;
            _spriteRect.x = _x;
        }
        else
        {
            right = false;
            _distanceMoved = 0;
        }
    }
    else if (!right)
    {
        if (!offScreen_x(right, _groundMoveSpeed, timeBetweenFrames) && _distanceMoved <= _maxMoveDistance)
        {
            _distanceMoved += _groundMoveSpeed * timeBetweenFrames;
            _x += _groundMoveSpeed * timeBetweenFrames;
            _spriteRect.x = _x;
        }
        else
        {
            right = true;
            _distanceMoved = 0;
        }
    }
}

void Enemy::update(float timeBetweenFrames)
{
    _moveVertically ? moveVertically(timeBetweenFrames) : moveHorizontally(timeBetweenFrames);
}

void Enemy::render(SDL_Renderer *renderer, float timeBetweenFrames)
{
    update(timeBetweenFrames);
    SDL_RenderCopy(renderer, _spriteTexture, &_cropRect, &_spriteRect);
}

#include "Enemy.hpp"
#include "GameWindow.hpp"


Enemy::Enemy()
{
}

void Enemy::init(SDL_Renderer *renderer, std::string textureFilePath, int numFramesX, int numFramesY,  bool moveVertically)
{
    initSprite(renderer, textureFilePath, numFramesX, numFramesY);
    
    _spriteRect.w = _spriteRect.h = 50;
    
    _moveVertically = moveVertically;
    _maxMoveDistance = 100.0f;
    _distanceMoved = 0.0f;
    _xVel = 100.0f;
}

void Enemy::setPos(int startXpos, int startYpos)
{
    _x = _spriteRect.x = startXpos;
    _y = _spriteRect.y = startYpos;
}

void Enemy::moveVertically(float timeBetweenFrames)
{
    static bool up = true;
    
    if (up)
    {
        if (!offScreen_y(up, _xVel, timeBetweenFrames) && _distanceMoved <= _maxMoveDistance)
        {
            _distanceMoved += _xVel * timeBetweenFrames;
            _y += -_xVel * timeBetweenFrames;
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
        if (!offScreen_y(false, _xVel, timeBetweenFrames) && _distanceMoved <= _maxMoveDistance)
        {
            _distanceMoved += _xVel * timeBetweenFrames;
            _y += _xVel * timeBetweenFrames;
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
    printf("%d, %d\n", _spriteRect.x, _spriteRect.y);
    printf("%d, %d\n", _spriteRect.w, _spriteRect.h);
    if (right)
    {
        if (!offScreen_x(right, _xVel, timeBetweenFrames) && _distanceMoved <= _maxMoveDistance)
        {
            _distanceMoved += _xVel * timeBetweenFrames;
            _x += -_xVel * timeBetweenFrames;
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
        if (!offScreen_x(right, _xVel, timeBetweenFrames) && _distanceMoved <= _maxMoveDistance)
        {
            _distanceMoved += _xVel * timeBetweenFrames;
            _x += _xVel * timeBetweenFrames;
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

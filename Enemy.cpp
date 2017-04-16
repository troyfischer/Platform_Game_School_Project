#include "Enemy.hpp"
#include "GameWindow.hpp"


Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::init(SDL_Renderer *renderer, std::string textureFilePath, int numFramesX, int numFramesY,  bool moveVertically, float maxMoveDistance, int id, int levelID)
{
    initSprite(renderer, textureFilePath, numFramesX, numFramesY);
    
    _spriteRect.w = _spriteRect.h = 40;
    _cropRect.x = _cropRect.y = 0;
    
    _moveVertically = moveVertically;
    _moveRight = true;
    _maxMoveDistance = maxMoveDistance;
    _id = id;
    _levelID = levelID;
    _distanceMoved = 0.0f;
    _xVel = 50.0f;
    _yVel = 75.0f;
    _frameCount = 0;
}

void Enemy::setPos(int startXpos, int startYpos)
{
    _x = _spriteRect.x = startXpos;
    _y = _spriteRect.y = startYpos;
}

void Enemy::moveVertically(float timeBetweenFrames)
{    
    if (_moveUp)
    {
        if (!offScreen_y(_moveUp, _yVel, timeBetweenFrames) && _distanceMoved <= _maxMoveDistance)
        {
            _distanceMoved += _yVel * timeBetweenFrames;
            _y += -_yVel * timeBetweenFrames;
            _spriteRect.y = _y;
        }
        else
        {
            _moveUp = false;
        }
    }
    else if (!_moveUp)
    {
        if (!offScreen_y(false, _yVel, timeBetweenFrames) && _distanceMoved + getSpriteHeight() >= -_maxMoveDistance)
        {
            _distanceMoved += -_yVel * timeBetweenFrames;
            _y += _yVel * timeBetweenFrames;
            _spriteRect.y = _y;
        }
        else
        {
            _moveUp = true;
        }
        
    }
}

void Enemy::moveHorizontally(float timeBetweenFrames)
{
    if (_moveRight)
    {
        if (!offScreen_x(_moveRight, _xVel, timeBetweenFrames) && _distanceMoved <= _maxMoveDistance)
        {
            _distanceMoved += _xVel * timeBetweenFrames;
            _x += _xVel * timeBetweenFrames;
            _spriteRect.x = _x;
            animate(_moveRight, timeBetweenFrames);
            
        }
        else
        {
            _moveRight = false;
        }
    }
    else if (!_moveRight)
    {
        if (!offScreen_x(_moveRight, _xVel, timeBetweenFrames) && _distanceMoved >= -_maxMoveDistance)
        {
            _distanceMoved += -_xVel * timeBetweenFrames;
            _x += -_xVel * timeBetweenFrames;
            _spriteRect.x = _x;
            animate(_moveRight, timeBetweenFrames);
        }
        else
        {
            _moveRight = true;
        }
    }
}

void Enemy::animate(bool right, float timeBetweenFrames)
{
    if (right)
    {
        if (_id == 2) //zombie animation
        {
            _cropRect.x = _spriteWidth;
            _frameCount += timeBetweenFrames;
            if (_frameCount >= 0.2f)
            {
                _frameCount = 0;
                _cropRect.y += _spriteHeight;
                if (_cropRect.y + _spriteHeight >= _textureHeight)
                {
                    _cropRect.y = 0;
                }
            }
        }
        else if (_id == 3) //spider animation
        {
            _cropRect.y = _spriteHeight;
            _frameCount += timeBetweenFrames;
            if (_frameCount >= 0.15f)
            {
                _frameCount = 0;
                _cropRect.x += _spriteWidth;
                if (_cropRect.x >= _textureWidth)
                {
                    _cropRect.x = 0;
                }
            }
        }
    }
    else
    {
        if (_id == 2) //zombie animation
        {
            _cropRect.x = 0;
            _frameCount += timeBetweenFrames;
            if (_frameCount >= 0.2f)
            {
                _frameCount = 0;
                _cropRect.y += _spriteHeight;
                if (_cropRect.y + _spriteHeight >= _textureHeight)
                {
                    _cropRect.y = 0;
                }
            }
        }
        else if (_id == 3) //spider animation
        {
            _cropRect.y = 0;
            _frameCount += timeBetweenFrames;
            if (_frameCount >= 0.15f)
            {
                _frameCount = 0;
                _cropRect.x += _spriteWidth;
                if (_cropRect.x >= _textureWidth)
                {
                    _cropRect.x = 0;
                }
            }
        }

    }
}

void Enemy::update(float timeBetweenFrames)
{
    _moveVertically ? moveVertically(timeBetweenFrames) : moveHorizontally(timeBetweenFrames);
}

int Enemy::getLevelID() { return _levelID; }

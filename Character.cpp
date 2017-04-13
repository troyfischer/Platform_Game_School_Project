#include "Character.hpp"
#include <sstream>

Character::Character()
{
}

void Character::init(SDL_Renderer *renderer, std::string textureFilePath, int numFramesX, int numFramesY)
{
    initSprite(renderer, textureFilePath, numFramesX, numFramesY);
    
    /* Setting the size of the main character */
    _spriteRect.w = _spriteRect.h = 50;
    
    /* Setting attributes */
    _lives = 3;
    _xVel = 100.0f;
    _inAirSpeed = 10.0f;
    _gravity = 1.0f;
    _yVel = -200.0f;
    _onGround = true;
    _isJumping = false;
    _touchingPlatform = false;
    _hitBottomOfPlatform = false;

    
    /* This portion will initialize the text on the screen that keeps the Character's lives */
    _livesText = NULL;
    std::stringstream textStream;
    textStream << "Lives: " << _lives;
    _livesText = new Text(renderer, textStream.str(), {0, 255, 255, 255},"/Users/Troy/Documents/workspace/Xcode/Working/Platformer/Platformer/Times New Roman.ttf", 20);

    _frameCount = 0;
}

void Character::initPos(int x, int y)
{
    /* Setting intital position of main character */
    _x = _spriteRect.x = x;
    _y = _spriteRect.y = y;
}

const Uint8 * Character::getKeyState()
{
    return SDL_GetKeyboardState(NULL);
}

void Character::jump(float timeBetweenFrames)
{
    const Uint8 *keyState = getKeyState();
    if (!_hitBottomOfPlatform)
    {
        if (keyState[SDL_SCANCODE_W] && _isJumping)
        {
            _y += _yVel * timeBetweenFrames;
            _spriteRect.y = _y;
        }
        else
        {
            _isJumping = false;
        }
    }
    else
    {
        _isJumping = false;
    }
}

void Character::applyGravity(float timeBetweenFrames, std::vector<Platform> &platforms)
{
    /* The purpose of gravity is to cause the _yVel to eventually be positive and 
     bring the character down */
    _gravity += 1;
}

void Character::resetJumpFields()
{
    _yVel = -200.0f;
    _onGround = true;
    _gravity = 1.0f;
}

void Character::update(float timeBetweenFrames, std::vector<Platform> &platforms)
{
    isCharacterOnPlatform(platforms);
    
    if (!_touchingPlatform)
    {
        _onGround = false;
        collisionUnderPlatform(platforms);
        applyGravity(timeBetweenFrames, platforms);
        _y += _gravity * timeBetweenFrames;
        _spriteRect.y = _y;
        if (_spriteRect.y > WINDOW_HEIGHT)
        {
            reset(platforms.at(0));
            resetJumpFields();
        }
    }
    else
    {
        if (!_isJumping)
        {
            
            if ((_y + getSpriteHeight()) + _gravity * timeBetweenFrames < _currentPlatform.getY())
            {
                applyGravity(timeBetweenFrames, platforms);
                _y += _gravity * timeBetweenFrames;
                _spriteRect.y = _y;
            }
            else
            {
                resetJumpFields();
            }
        }
    }
    
    
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
        if (!offScreen_x(false, _xVel, timeBetweenFrames))
        {
            _x += -_xVel * timeBetweenFrames;
            _spriteRect.x = _x;
        }
        animateRunning(keyState, isMoving, timeBetweenFrames);
    }
    else if (keyState[SDL_SCANCODE_D])
    {
        //rightward movement
        if (!offScreen_x(true, _xVel, timeBetweenFrames))
        {
            _x += _xVel * timeBetweenFrames;
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
    }
    _touchingPlatform = false;
    _hitBottomOfPlatform = false;
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

void Character::makesCollision(Enemy &e)
{
    /* Collisions will be circular based and use the pythagorean theorem
     The method works as long as each sprite has an equivalent length and widths */
    
    float distance = sqrtf(powf(_x_Origin - e._x_Origin, 2.0f) + powf(_y_Origin - e._spriteRect.y, 2.0f));
    if (distance <= _radius + e.get_radius())
    {
        printf("Collision\n");
    }
    
}

void Character::collisionUnderPlatform(std::vector<Platform> &platforms)
{
    std::vector<Platform>::iterator iter;
    for (iter = platforms.begin(); iter != platforms.end(); ++iter)
    {
        if (iter->getX() != _currentPlatform.getX() || iter->getY() != _currentPlatform.getY())
        {
            if (_y + _spriteRect.h >= iter->getY() + iter->getH())
            {
                if (_x + _spriteRect.w >= iter->getX() && _x <= iter->getX() + iter->getW())
                {
                    if (_y <= iter->getY() + iter->getH())
                    {
                        _hitBottomOfPlatform = true;
                        break;
                    }
                }
            }
        }
    }
}

void Character::isCharacterOnPlatform(std::vector<Platform> &platforms)
{
    std::vector<Platform>::iterator iter;
    for (iter = platforms.begin(); iter != platforms.end(); ++iter)
    {
        if (get_x_Origin() + _spriteRect.w/4 >= iter->getX() && get_x_Origin() - _spriteRect.w/4 <= iter->getX() + iter->getW())
        {
            if (_y + getSpriteHeight() <= iter->getY() + buffer && _y + getSpriteHeight() >= iter->getY() - buffer)
            {
                _touchingPlatform = true;
                _currentPlatform = *iter;
                break; //break the loop
            }
        }
    }
}

void Character::render(SDL_Renderer *renderer, float timeBetweenFrames)
{
    SDL_RenderCopy(renderer, _spriteTexture, &_cropRect, &_spriteRect);
    _livesText->renderText(renderer, 0, 0, 50, 50);
}


void Character::reset(Platform &start)
{
    _x = _spriteRect.x = start.getX();
    _y = _spriteRect.y = start.getY() - _spriteRect.h;
    _cropRect.y = _spriteHeight;
    _cropRect.x = _spriteWidth;
}



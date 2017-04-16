#include "Character.hpp"
#include <sstream>

Character::Character()
{
}

Character::~Character()
{
}

void Character::init(SDL_Renderer *renderer, std::string textureFilePath, int numFramesX, int numFramesY)
{
    /* Calling parent class initialization*/
    initSprite(renderer, textureFilePath, numFramesX, numFramesY);
    
    /* Setting the size of the main character */
    _spriteRect.w = _spriteRect.h = 50;
    
    /* Setting attributes */
    _lives = 3;
    _invincible = false;
    _completedLevel = false;
    _xVel = 100.0f;
    _yVel = -450.0f;
    
    _gravity = 0.0f;
    
    /* Used in determing whether the character is allowed to
     continue jumping, moving right, moving left etc*/
    _onGround = true;
    _isJumping = false;
    _hitBottomOfPlatform = false;
    _onPlatform = false;
    
    /* Used in the character animation ensuring the next frame of the sprite
     shows roughly every 0.2 seconds*/
    _frameCount = 0;
    
    /* All the music/sounds that will be played */
    _gameMusic = new Music("/Users/Troy/Documents/workspace/Xcode/Working/Platformer/Platformer/music.wav");
    _jumpSound = new Music("/Users/Troy/Documents/workspace/Xcode/Working/Platformer/Platformer/jump.wav");
    _invincibilityMusic = new Music("/Users/Troy/Documents/workspace/Xcode/Working/Platformer/Platformer/invincible.wav");
    _1upSound = new Music("/Users/Troy/Documents/workspace/Xcode/Working/Platformer/Platformer/1-up.wav");
    _deathSound = new Music("/Users/Troy/Documents/workspace/Xcode/Working/Platformer/Platformer/death.wav");
    
    _gameMusic->playMusic();
}

void Character::setPos(int x, int y)
{
    /* Setting intital position of main character */
    _x = _spriteRect.x = x;
    _y = _spriteRect.y = y;
}

void Character::jump(float timeBetweenFrames)
{
    
    const Uint8 *keyState = SDL_GetKeyboardState(NULL);
    
    if (!_hitBottomOfPlatform)
    {
        //if the character has not hit the underside of a platform his _y position can decrease
        animateInAir(keyState, timeBetweenFrames);
        if (keyState[SDL_SCANCODE_W] && _isJumping)
        {
            /* _isJumping makes it so that once W is released the player cannot
             jump again until it lands on a platform */
            _y += _yVel * timeBetweenFrames;
            _spriteRect.y = _y;
            _yVel += 10; //slow the jump speed as the character gets higher
        }
        else
        {
            //the user let go of the W key
            _isJumping = false;
        }
        if (keyState[SDL_SCANCODE_A])
        {
            //allow the character to move left while in the air as long as it is not outside of the screen
            if (!offScreen_x(false, _xVel, timeBetweenFrames))
            {
                _x += -_xVel * timeBetweenFrames;
                _spriteRect.x = _x;
            }
        }
        if (keyState[SDL_SCANCODE_D])
        {
            //allow the character to move right in the air as long as it is not outside of the screen
            if (!offScreen_x(true, _xVel, timeBetweenFrames))
            {
                _x += _xVel * timeBetweenFrames;
                _spriteRect.x = _x;
            }
        }
    }
    else
    {
        //The character hit the underside of a platform and his _y is no longer allowed to decrease
        _isJumping = false;
    }
}

void Character::applyGravity()
{
    //increase the speed at which the character falls
    _gravity += 10;
}

void Character::resetJumpFields()
{
    //resets all the variables involved in jumping
    _yVel = -450.0f;
    _onGround = true;
    _gravity = 0.0f;
}

void Character::update(float timeBetweenFrames, std::vector<Platform *> &platforms)
{
    static bool playedJumpSound = false; //ensures the jump sound is played only once per jump
    static float frameCount = 0; //once the character reaches a platform 0.2 seconds must pass before it can jump again
    static bool canJump = true; //ensures frameCount has reached 0.2
    
    _hitBottomOfPlatform = collisionUnderPlatform(platforms, timeBetweenFrames); //see method below
    _onPlatform = isCharacterOnPlatform(platforms); //see method below
    
    if (!_onPlatform)
    {
        /* If the character is not on a platform it cannot jump and should also be falling */
        canJump = false;
        _onGround = false;
        applyGravity();
        _y += _gravity * timeBetweenFrames;
        _spriteRect.y = _y;
        if (_spriteRect.y > WINDOW_HEIGHT)
        {
            //if the character falls off the map
            reset(*(platforms.at(0)));
            resetJumpFields();
        }
    }
    else
    {
        if (!_isJumping)
        {
            //lower the player flush with the current platform
            if ((_y + _spriteRect.h) < _currentPlatform.getY())
            {
                _y += 0.8;
                _spriteRect.y = _y;
            }
        }
        
        resetJumpFields();
        _onGround = true;
        playedJumpSound = false; //allow the jump sound to be played agian
        frameCount += timeBetweenFrames;
        if (frameCount >= 0.2f)
        {
            //the player can now jump again
            frameCount = 0;
            canJump = true;
        }
    }
    
    bool isMoving = true;
    
    const Uint8 *keyState = SDL_GetKeyboardState(NULL);
    
    if (_onGround && canJump && keyState[SDL_SCANCODE_W])
    {
        //jump
        _isJumping = true;
        _onGround = false; //allows the jump method to be called below
        if (!playedJumpSound)
        {
            //sound only gets played once per jump
            playedJumpSound = true;
            _jumpSound->playSound();
        }
    }
    else if (_onPlatform && keyState[SDL_SCANCODE_A] && !collisionLeftSidePlatform(platforms))
    {
        //leftward movement
        if (!offScreen_x(false, _xVel, timeBetweenFrames))
        {
            //the character can move left as long as his _x position is not less than 0
            _x += -_xVel * timeBetweenFrames;
            _spriteRect.x = _x;
        }
        animateRunning(keyState, isMoving, timeBetweenFrames);
    }
    else if (_onPlatform && keyState[SDL_SCANCODE_D] && !collisionRightSidePlatform(platforms))
    {
        //rightward movement
        if (!offScreen_x(true, _xVel, timeBetweenFrames))
        {
            //the character can move right as long as his _x + width is less than the screen width
            _x += _xVel * timeBetweenFrames;
            _spriteRect.x = _x;
        }
        animateRunning(keyState, isMoving, timeBetweenFrames);
    }
    else
    {
        isMoving = false; //if no keys are pressed the character is not moving (unless due to gravity)
        animateRunning(keyState, isMoving, timeBetweenFrames);
    }
    
    if (!_onGround)
    {
        jump(timeBetweenFrames);
    }
}

void Character::animateInAir(const Uint8 *keyState, float timeBetweenFrames)
{
    /* The air animation is the character in a static running position */
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
}

void Character::animateRunning(const Uint8 *keyState, bool isMoving, float timeBetweenFrames)
{
    /* This method is completely dependent on the sprite sheet used */
    
    _cropRect.h = _spriteHeight; //makes the cropping cleaner
    
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
            //shows the next frame every 0.15 seconds
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

bool Character::enemyCollision(Enemy &e)
{
    /* Collisions are circular based and use the pythagorean theorem
     The method works best when the sprite has equal length and width */
    
    float distance = sqrtf(powf(get_x_Origin() - e.get_x_Origin(), 2.0f) + powf(get_y_Origin() - e.get_y_Origin(), 2.0f));
    if (distance <= get_radius() + e.get_radius() - 20)
    {
        return true;
    }
    return false;
}

bool Character::itemCollision(Item &i)
{
    /* Collisions are circular based and use the pythagorean theorem
     The method works best when the sprite has equal length and width */
    
    float distance = sqrtf(powf(get_x_Origin() - i.get_x_Origin(), 2.0f) + powf(get_y_Origin() - i.get_y_Origin(), 2.0f));
    if (distance <= get_radius())
    {
        switch (i.getID())
        {
            //apply the status effect based on what item is collided with
            case 1: ++_lives;
                    _1upSound->playSound();
                    break;
            case 2: _invincible = true;
                    _gameMusic->endMusic();
                    _invincibilityMusic->playMusic();
                    break;
            case 3: _completedLevel = true;
                    return true;
                    break;
            default: break;
        }
        return true;
    }
    return false;
}

bool Character::collisionUnderPlatform(std::vector<Platform *> &platforms, float timeBetweenFrames)
{
    if (offScreen_y(true, _yVel, timeBetweenFrames))
    {
        return true;
    }
    else
    {
        for (auto iter = platforms.begin(); iter != platforms.end(); ++iter)
        {
            if ((*iter)->getX() != _currentPlatform.getX() || (*iter)->getY() != _currentPlatform.getY())
            {
                //platform is not the current platform
                if (_y + _spriteRect.h >= (*iter)->getY() + (*iter)->getH())
                {
                    //player is underneath the platform
                    if (get_x_Origin() + _spriteRect.w/5 - buffer >= (*iter)->getX() && get_x_Origin() - _spriteRect.w/5 <= (*iter)->getX() + (*iter)->getW())
                    {
                        
                        if (_y <= (*iter)->getY() + (*iter)->getH())
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool Character::collisionRightSidePlatform(std::vector<Platform *> &platforms)
{
    for (auto iter = platforms.begin(); iter != platforms.end(); ++iter)
    {
        if ((*iter)->getX() != _currentPlatform.getX() || (*iter)->getY() != _currentPlatform.getY())
        {
            //platform is not the current platform
            if (_y + _spriteRect.h >= (*iter)->getY() + (*iter)->getH() && _y - buffer <= (*iter)->getY())
            {
                //within the platform's _y range
                if (_x + _spriteRect.w - 15 >= (*iter)->getX() && _x +_spriteRect.w <= (*iter)->getX() + (*iter)->getW())
                {
                    //within the platform's _x range
                    return true;
                }
            }
        }
    }
    return false;
}

bool Character::collisionLeftSidePlatform(std::vector<Platform *> &platforms)
{
    for (auto iter = platforms.begin(); iter != platforms.end(); ++iter)
    {
        if ((*iter)->getX() != _currentPlatform.getX() || (*iter)->getY() != _currentPlatform.getY())
        {
            //platform is not the current platform
            if (_y + _spriteRect.h >= (*iter)->getY() + (*iter)->getH() && _y - buffer <= (*iter)->getY())
            {
                //within the platform's _y range
                if (_x <= (*iter)->getX() + (*iter)->getW() && _x >= (*iter)->getX())
                {
                    //within the platform's _x range
                    return true;
                }
            }
        }
    }
    return false;
}

bool Character::isCharacterOnPlatform(std::vector<Platform *> &platforms)
{
    for (auto iter = platforms.begin(); iter != platforms.end(); ++iter)
    {
        if (get_x_Origin() + _spriteRect.w/7.0f >= (*iter)->getX() && get_x_Origin() - _spriteRect.w/7.0 <= (*iter)->getX() + (*iter)->getW())
        {
            //within the platform's _x range
            if (_y + _spriteRect.h <= (*iter)->getY() + buffer && _y + _spriteRect.h >= (*iter)->getY() - buffer)
            {
                //the character has a range of _y values it can be between which ensures that every collision is caught
                _currentPlatform = **iter;
                return true;
            }
        }
    }
    return false;
}

void Character::reset(Platform &start)
{
    //method resets the character on the desired platform sent to the method
    if (!_completedLevel)
    {
        --_lives;
        _gameMusic->endMusic();
        //mario esque enemy collision scene
        _deathSound->playSound();
        SDL_Delay(1500);
        _gameMusic->playMusic();
    }
    if (_invincible) loseInvincibility();
    _completedLevel = false;
    _x = _spriteRect.x = start.getX();
    _y = _spriteRect.y = start.getY() - _spriteRect.h;
    _cropRect.y = _spriteHeight;
    _cropRect.x = _spriteWidth;
}

//setters and getters
float Character::getSpriteHeight() { return _spriteRect.h; }
int Character::getLives() { return _lives; }
void Character::newGame() { _lives = 3; }
bool Character::completedLevel() { return _completedLevel; }
bool Character::isInvincible() { return _invincible; }

void Character::loseInvincibility()
{
    _invincible = false;
    _invincibilityMusic->endMusic();
    _gameMusic->playMusic();
}




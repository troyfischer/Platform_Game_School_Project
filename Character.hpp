#ifndef Character_hpp
#define Character_hpp

#include <SDL2_mixer/SDL_mixer.h>
#include <stdio.h>
#include <cmath>
#include <vector>
#include "GameWindow.hpp"
#include "Sprite.hpp"
#include "Enemy.hpp"
#include "Platform.hpp"
#include "Item.hpp"
#include "Music.hpp"

class Character : public Sprite
{
    /* The Character class is a friend of the Sprite class and thus
     has acess to everything in the Sprite class */
private:
    /*---------------------In game music/sounds------------------------*/
    Music *_gameMusic;
    Music *_jumpSound;
    Music *_invincibilityMusic;
    Music *_1upSound;
    Music *_deathSound;
    bool _playSound;
    
    /* Holds the current platform the character is standing on */
    Platform _currentPlatform;
    
    /*------------------Character attributes--------------------------*/
    int _lives;
    bool _invincible;
    bool _completedLevel;
    
    /* -------------------Jumping related fields--------------------*/
    float _gravity;
    bool _onGround;
    bool _isJumping;
    bool _hitBottomOfPlatform;
    bool _onPlatform;
    const int buffer = 10;
    
    /*---------------------Regulates animation-----------------------*/
    float _frameCount;
    
    /*--------------------Jumping related methods-----------------------*/
    void jump(float timeBetweenFrames);
    void applyGravity();
    void resetJumpFields();
    
    /*---------------------Animation methods------------------*/
    void animateInAir(const Uint8 *keyState, float timeBetweenFrames);
    void animateRunning(const Uint8 *keyState, bool isMoving, float timeBetweenFrames);
    
    /*----------------Checks for collisions with platforms----------------------*/
    bool collisionUnderPlatform(std::vector<Platform *> &platforms, float timeBetweenFrames);
    bool collisionRightSidePlatform(std::vector<Platform *> &platforms);
    bool collisionLeftSidePlatform(std::vector<Platform *> &platforms);
    bool isCharacterOnPlatform(std::vector<Platform *> &platforms);
    
public:
    /*-------------Constructor/Destructor------------------*/
    Character();
    ~Character();
    
    /*--------Methods to initialize and set position------------*/
    void init(SDL_Renderer *renderer, std::string textureFilePath, int numFramesX, int numFramesY);
    void setPos(int x, int y);
    
    /*-----------------Moves the character------------------------*/
    void update(float timeBetweenFrames, std::vector<Platform *> &platforms);
    
    /*------------Checks for collisions with enemies and items-------------*/
    bool enemyCollision(Enemy &e);
    bool itemCollision(Item &i);
    
    /*-------------Resets characters fields and position------------------*/
    void reset(Platform &start);
    
    /*--------------Setters and Getters--------------------*/
    float getSpriteHeight();
    int getLives();
    void newGame();
    bool completedLevel();
    bool isInvincible();
    void loseInvincibility();
};

#endif /* Character_hpp */

#ifndef Character_hpp
#define Character_hpp

#include <stdio.h>
#include <cmath>
#include <vector>
#include "GameWindow.hpp"
#include "Text.hpp"
#include "Enemy.hpp"
#include "Sprite.hpp"
#include "Platform.hpp"

class Character : public Sprite
{
private:
    Platform _currentPlatform;
    /* ---------------------Attributes----------------------- */
    int _lives;
    
    /* -----------------Gravity Attributes------------------- */
    float _gravity;
    float _yVel;
    float _inAirSpeed;
    bool _onGround;
    bool _isJumping;
    bool _touchingPlatform;
    bool _hitBottomOfPlatform;
    const int buffer = 10;
    
    /* Used during animation */
    float _frameCount;
    
    /* The Text object will be there so the lives can be updated from the Character class */
    Text *_livesText;
    
    const Uint8 * getKeyState();
    /* -------------------Movement methods------------------------ */
    
public:
    Character(SDL_Renderer *renderer, std::string textureFilePath, int numFramesX, int numFramesY);
    Character();
    void init(SDL_Renderer *renderer, std::string textureFilePath, int numFramesX, int numFramesY);
    void initPos(int x, int y);
    void render(SDL_Renderer *renderer, float timeBetweenFrames) override;
    bool collisionOverPlatform(Platform &platform);
    void jump(float timeBetweenFrames);
    void applyGravity(float timeBetweenFrames, std::vector<Platform> &platforms);
    void resetJumpFields();
    void animateInAir(const Uint8 *keyState, float timeBetweenFrames);
    void animateRunning(const Uint8 *keyState, bool isMoving, float timeBetweenFrames);
    void update(float timeBetweenFrames, std::vector<Platform> &platforms);
    void makesCollision(Enemy &e);
    void collisionUnderPlatform(std::vector<Platform> &platforms);
    void isCharacterOnPlatform(std::vector<Platform> &platforms);
    void reset(Platform &start);
    Platform getCurrentPlatform();

};

#endif /* Character_hpp */

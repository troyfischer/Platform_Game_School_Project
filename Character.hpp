#ifndef Character_hpp
#define Character_hpp

#include <stdio.h>
#include <cmath>
#include "GameWindow.hpp"
#include "Text.hpp"
#include "Enemy.hpp"
#include "Sprite.hpp"
#include "Platform.hpp"

class Character : public Sprite
{
private:
    /* ---------------------Attributes----------------------- */
    int _lives;
    
    /* -----------------Gravity Attributes------------------- */
    float _gravity;
    int _jumpSpeed;
    float _inAirSpeed;
    bool _onGround;
    bool _isJumping;
    bool _onPlatform;
    
    /* Used during animation */
    float _frameCount;
    
    /* The Text object will be there so the lives can be updated from the Character class */
    Text *_livesText;
    
    const Uint8 * getKeyState();
    /* -------------------Movement methods------------------------ */
    void jump(float timeBetweenFrames);
    void applyGravity(float timeBetweenFrames, Platform &platform);
    void resetJumpFields();
    void animateInAir(const Uint8 *keyState, float timeBetweenFrames);
    void animateRunning(const Uint8 *keyState, bool isMoving, float timeBetweenFrames);
    void update(float timeBetweenFrames) override;
    void update(float timeBetweenFrames, Platform &platform);
    void makesCollision(Enemy *e);
    void collisionUnderPlatform(Platform &platform);
public:
    Character(SDL_Renderer *renderer, std::string textureFilePath, int numFramesX, int numFramesY);
    void render(SDL_Renderer *renderer, float timeBetweenFrames, Platform &platform);
    void render(SDL_Renderer *renderer, float timeBetweenFrames) override;
    bool collisionOverPlatform(Platform &platform);

};

#endif /* Character_hpp */

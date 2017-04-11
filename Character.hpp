#ifndef Character_hpp
#define Character_hpp

#include <stdio.h>
#include <cmath>
#include "GameWindow.hpp"
#include "Text.hpp"
#include "Enemy.hpp"
#include "Sprite.hpp"

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
    
    /* Used during animation */
    float _frameCount;
    
    /* The Text object will be there so the lives can be updated from the Character class */
    Text *_livesText;
    
    const Uint8 * getKeyState();
    /* -------------------Movement methods------------------------ */
    void jump(float timeBetweenFrames);
    void applyGravity(float timeBetweenFrames);
    void resetJumpFields();
    void animateInAir(const Uint8 *keyState, float timeBetweenFrames);
    void animateRunning(const Uint8 *keyState, bool isMoving, float timeBetweenFrames);
    void update(float timeBetweenFrames) override;
    void makesCollision(Enemy *e);
public:
    Character(SDL_Renderer *renderer, std::string textureFilePath, int numFramesX, int numFramesY);
    void render(SDL_Renderer *renderer, float timeBetweenFrames) override;
};

#endif /* Character_hpp */

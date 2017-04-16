#ifndef Enemy_hpp
#define Enemy_hpp

#include "Sprite.hpp"

/* Enemy's will oscillate vertically or horizontally */

class Enemy : public Sprite
{
    /* The Enemy class is a friend of the Sprite class and thus
     has acess to everything in the Sprite class */
private:
    int _levelID;
    /* levelID correspondence
     1. Level 1
     2. Level 2
     3. Level 3*/
    
    int _id;
    /* ID correspondence
     1. fireball
     2. zombie
     3. spider */
    
    /*------------Regulates animation---------------*/
    float _frameCount;
    
    /* Enemy will move vertically if true and horizontally if false */
    bool _moveVertically;
    
    bool _moveRight; //determines right vs left movement
    bool _moveUp; //determines up vs down movement
    
    /* ------------------------Attributes---------------------------- */
    float _maxMoveDistance;
    float _distanceMoved;
    
    /* ----------------------Movement methods------------------------- */
    void moveVertically(float timeBetweenFrames);
    void moveHorizontally(float timeBetweenFrames);
    
    /*--------------------Animation---------------------------*/
    void animate(bool right, float timeBetweenFrames);
    
public:
    /*-------------Constructor/Destructor------------------*/
    Enemy();
    ~Enemy();
    
    /*--------Methods to initialize and set position------------*/
    void init(SDL_Renderer *renderer, std::string textureFilePath, int numFramesX, int numFramesY, bool moveVertically, float maxMoveDistance, int id, int levelID);
    void setPos(int startXpos, int startYpos);
    
    /*-----------------Moves the enemy------------------------*/
    void update(float timeBetweenFrames);
    
    /*--------------Setters and Getters--------------------*/
    int getLevelID();
};

#endif /* Enemy_hpp */

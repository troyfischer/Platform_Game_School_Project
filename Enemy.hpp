#ifndef Enemy_hpp
#define Enemy_hpp

#include "Sprite.hpp"

/* Enemy's will either move back and forth vertically or horizontally */

class Enemy : public Sprite
{
private:
    /* Enemy will move vertically if true and horizontally if false */
    bool _moveVertically;
    
    /* ------------------------Attributes---------------------------- */
    float _maxMoveDistance;
    float _distanceMoved;
    
    /* ----------------------Movement methods------------------------- */
    void moveVertically(float timeBetweenFrames);
    void moveHorizontally(float timeBetweenFrames);
    void update(float timeBetweenFrames);
public:
    Enemy();
    void init(SDL_Renderer *renderer, std::string textureFilePath, int numFramesX, int numFramesY, bool moveVertically);
    void setPos(int startXpos, int startYpos);
    void render(SDL_Renderer *renderer, float timeBetweenFrames) override;
};

#endif /* Enemy_hpp */

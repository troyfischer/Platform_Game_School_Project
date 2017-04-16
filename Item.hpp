#ifndef Item_hpp
#define Item_hpp

#include <stdio.h>
#include "Sprite.hpp"

class Item : public Sprite
{
    /* The Item class is a friend of the Sprite class and thus
     has acess to everything in the Sprite class */
private:
    int _levelID;
    /* levelID correspondence
     1. Level 1
     2. Level 2
     3. Level 3*/
    
    int _id;
    /* ID correspondence
     1. life
     2. invincible
     3. door - for level completion */
public:
    /*-------------Constructor/Destructor------------------*/
    Item();
    ~Item();
    
    /*------------Methods to initialize and set position------------*/
    void init(SDL_Renderer *renderer, std::string textureFilePath, int numFramesX, int numFramesY, int id, int levelID);
    void setPos(int x, int y);
    
    /*--------------Setters and Getters--------------------*/
    int getID();
    int getLevelID();
};

#endif /* Item_hpp */

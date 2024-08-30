#include "Item.hpp"

Item::Item()
{
}

Item::~Item()
{
}

void Item::init(SDL_Renderer *renderer, std::string textureFilePath, int numFramesX, int numFramesY, int id, int levelID)
{
    initSprite(renderer, textureFilePath, 1, 1);
    _spriteRect.w = _spriteRect.h = 50;
    _id = id;
    _levelID = levelID;
}

void Item::setPos(int x, int y)
{
    _x = _spriteRect.x = x;
    _y = _spriteRect.y = y;
}

int Item::getID() { return _id; }
int Item::getLevelID() { return _levelID; }

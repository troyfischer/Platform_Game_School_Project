
#include "Map.hpp"

Map::Map()
{
}

void Map::initConstants(SDL_Renderer *renderer)
{
    
    //create hero
    _hero.init(renderer, "/Users/Troy/Documents/workspace/Xcode/Working/Platformer/Platformer/SpriteSheet.png", 4, 4);
    
    //load background
    SDL_Surface *temp = IMG_Load("/Users/Troy/Documents/workspace/Xcode/Working/DungeonEscape/DungeonEscape/background.jpg");
    _background = SDL_CreateTextureFromSurface(renderer, temp);
    SDL_FreeSurface(temp);
    
    
    
}

void Map::loadMap1(SDL_Renderer *renderer)
{
    Platform plat1; plat1.setPlatform(0, WINDOW_HEIGHT - plat1.getH());
    Platform plat2; plat2.setPlatform(plat1.getX(), plat1.getY() - 100);
    Platform plat3; plat3.setPlatform(plat2.getX() + plat2.getW(), plat2.getY() - 20);
    Platform plat4; plat4.setPlatform(plat3.getX() + plat3.getW(), plat3.getY() - 20);
    Platform plat5; plat5.setPlatform(plat4.getX() + plat4.getW(), plat4.getY() - 20);
    Platform plat6; plat6.setPlatform(plat5.getX() + plat5.getW(), plat5.getY() - 20);
    Platform plat7; plat7.setPlatform(plat6.getX() + plat6.getW(), plat6.getY() - 20);
    Platform plat8; plat8.setPlatform(plat7.getX() + plat7.getW(), plat7.getY() - 20);
    Platform plat9; plat9.setPlatform(plat8.getX() + plat8.getW(), plat8.getY() - 20);
    
    platforms.push_back(plat1);
    platforms.push_back(plat2);
    //platforms.push_back(plat3);
    platforms.push_back(plat4);
    platforms.push_back(plat5);
    //platforms.push_back(plat6);
    platforms.push_back(plat7);
    platforms.push_back(plat8);
    platforms.push_back(plat9);
    
    _hero.initPos(plat1.getX(), plat1.getY() - _hero.getSpriteHeight());

    Enemy bad;
    bad.init(renderer, "/Users/Troy/Documents/workspace/Xcode/Working/Platformer/Platformer/enemyspritesheet.png", 1, 1, false);
    bad.setPos(plat4.getX(), 0);
    
    enemies.push_back(bad);
}

void Map::showMap1(SDL_Renderer *renderer, float timeBetweenFrames)
{
    //render the background
    SDL_RenderCopy(renderer, _background, NULL, NULL);
    
    //update hero
    _hero.update(timeBetweenFrames, platforms);
    _hero.render(renderer, timeBetweenFrames);
   
    //render platforms
    for (auto iter = platforms.begin(); iter != platforms.end(); ++iter)
    {
        iter->show(renderer);
    }
    
    //render enemies
    for (auto iter = enemies.begin(); iter != enemies.end(); ++iter)
    {
        iter->render(renderer, timeBetweenFrames);
    }
    
    
    
}

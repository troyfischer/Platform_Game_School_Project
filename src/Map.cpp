#include "Map.hpp"

Map::Map()
{
    _canCreateMap = true;
    _canShowMap = false;
    currentMap = 1;
    _renderWin = false;
}

Map::~Map()
{
}

void Map::init(SDL_Renderer *renderer)
{
    _startScreen = new StartScreen(renderer);
    _loseScreen = new LoseScreen(renderer);
    _winScreen = new WinScreen(renderer);
    
    //create hero
    _hero.init(renderer, "./resources/images/characterSprite.png", 4, 4);
    
    //load background
    SDL_Surface *temp = IMG_Load("./resources/images/background.jpg");
    _background = SDL_CreateTextureFromSurface(renderer, temp);
    SDL_FreeSurface(temp);
    
    std::stringstream ss;
    ss << "Lives: " << _hero.getLives();
    _heroLivesText = new Text(renderer, ss.str(), {255,0,0,255}, "./resources/fonts/Times New Roman.ttf", 20);
}

void Map::createMap1(SDL_Renderer *renderer)
{
    /* Platforms were hard coded in for lack of a better method */
    
    //(x, y, width of platform, level ID)
    Platform * plat1 = new Platform(); plat1->setPlatform(0, 600, 100, 3); platforms.push_back(plat1);
    Platform * plat2 = new Platform(); plat2->setPlatform(150, 550, 75, 3); platforms.push_back(plat2);
    Platform * plat3 = new Platform(); plat3->setPlatform(200, 500, 75, 3); platforms.push_back(plat3);
    Platform * plat4 = new Platform(); plat4->setPlatform(285, 450, 100, 3); platforms.push_back(plat4);
    Platform * plat5 = new Platform(); plat5->setPlatform(175, 400, 50, 1); platforms.push_back(plat5);
    Platform * plat6 = new Platform(); plat6->setPlatform(125, 325, 50, 1); platforms.push_back(plat6);
    Platform * plat7 = new Platform(); plat7->setPlatform(0, 275, 100, 1); platforms.push_back(plat7);
    Platform * plat8 = new Platform(); plat8->setPlatform(100, 200, 75, 1); platforms.push_back(plat8);
    Platform * plat9 = new Platform(); plat9->setPlatform(225, 175, 50, 1); platforms.push_back(plat9);
    Platform * plat10 = new Platform(); plat10->setPlatform(100, 120, 25, 1); platforms.push_back(plat10);
    Platform * plat11 = new Platform(); plat11->setPlatform(225, 50, 75, 1); platforms.push_back(plat11);
    Platform * plat12 = new Platform(); plat12->setPlatform(325, 200, 75, 1); platforms.push_back(plat12);
    Platform * plat13 = new Platform(); plat13->setPlatform(400, 125, 50, 1); platforms.push_back(plat13);
    Platform * plat14 = new Platform(); plat14->setPlatform(460, 90, 50, 1); platforms.push_back(plat14);
    Platform * plat15 = new Platform(); plat15->setPlatform(525, 125, 50, 1); platforms.push_back(plat15);
    Platform * plat16 = new Platform(); plat16->setPlatform(600, 90, 50, 1); platforms.push_back(plat16);
    Platform * plat17 = new Platform(); plat17->setPlatform(710, 125, 50, 1); platforms.push_back(plat17);
    Platform * plat18 = new Platform(); plat18->setPlatform(825, 125, 50, 3); platforms.push_back(plat18);
    Platform * plat19 = new Platform(); plat19->setPlatform(925, 100, 75, 3); platforms.push_back(plat19);
    Platform * plat21 = new Platform(); plat21->setPlatform(450, 425, 25, 2); platforms.push_back(plat21);
    Platform * plat22 = new Platform(); plat22->setPlatform(500, 375, 25, 2); platforms.push_back(plat22);
    Platform * plat23 = new Platform(); plat23->setPlatform(550, 325, 25, 2); platforms.push_back(plat23);
    Platform * plat24 = new Platform(); plat24->setPlatform(625, 275, 25, 2); platforms.push_back(plat24);
    Platform * plat25 = new Platform(); plat25->setPlatform(675, 225, 25, 2); platforms.push_back(plat25);
    Platform * plat26 = new Platform(); plat26->setPlatform(400, 645, 400, 3); platforms.push_back(plat26);
    Platform * plat27 = new Platform(); plat27->setPlatform(725, 300, 50, 3); platforms.push_back(plat27);
    Platform * plat28 = new Platform(); plat28->setPlatform(800, 570, 25, 3); platforms.push_back(plat28);
    Platform * plat29 = new Platform(); plat29->setPlatform(860, 530, 50, 3); platforms.push_back(plat29);
    Platform * plat30 = new Platform(); plat30->setPlatform(950, 500, 25, 3); platforms.push_back(plat30);
    Platform * plat31 = new Platform(); plat31->setPlatform(890, 450, 25, 3); platforms.push_back(plat31);
    Platform * plat32 = new Platform(); plat32->setPlatform(810, 370, 50, 3); platforms.push_back(plat32);
    Platform * plat33 = new Platform(); plat33->setPlatform(925, 330, 75, 3); platforms.push_back(plat33);
    Platform * plat34 = new Platform(); plat34->setPlatform(825, 255, 75, 3); platforms.push_back(plat34);
    Platform * plat35 = new Platform(); plat35->setPlatform(925, 175, 75, 3); platforms.push_back(plat35);
    Platform * plat36 = new Platform(); plat36->setPlatform(250, 275, 50, 1); platforms.push_back(plat36);
    
    //set hero's initial position
    _hero.setPos(plat1->getX(), plat1->getY() - _hero.getSpriteHeight());
    
    /* Creation of Enemies */
    Enemy * zombie = new Enemy();
    zombie->init(renderer, "./resources/images/zombie.png", 2, 3, false, plat26->getW()/2, 2, 3);
    zombie->setPos((plat26->getX() + plat26->getW()/2) - zombie->getSpriteWidth()/2, plat26->getY() - zombie->getSpriteHeight());
    Enemy * fireball = new Enemy();
    fireball->init(renderer, "./resources/images/fireball.png", 1, 1, true, 50, 1, 2);
    fireball->setPos((plat24->getX() + plat24->getW()/2) - fireball->getSpriteWidth()/2, plat24->getY() - fireball->getSpriteHeight());
    Enemy * spider = new Enemy();
    spider->init(renderer, "./resources/images/spiderspritesheet.png", 4, 2, false, plat7->getW()/2, 3, 1);
    spider->setPos((plat7->getX() + plat7->getW()/2) - spider->getSpriteWidth()/2, plat7->getY() - spider->getSpriteHeight());
    Enemy * zombie2 = new Enemy();
    zombie2->init(renderer, "./resources/images/zombie.png", 2, 3, false, plat11->getW()/2, 2, 1);
    zombie2->setPos((plat11->getX() + plat11->getW()/2) - zombie2->getSpriteWidth()/2, plat11->getY() - zombie2->getSpriteHeight());
    Enemy * fireball1 = new Enemy();
    fireball1->init(renderer, "./resources/images/fireball.png", 1, 1, true, 50, 1, 3);
    fireball1->setPos((plat30->getX() + plat30->getW()/2) - fireball1->getSpriteWidth()/2, plat30->getY() - fireball1->getSpriteHeight()); //platform 30
    Enemy * fireball2 = new Enemy();
    fireball2->init(renderer, "./resources/images/fireball.png", 1, 1, true, 50, 1, 2);
    fireball2->setPos(810 + 50/2 - fireball2->getSpriteWidth()/2, 370 - fireball2->getSpriteHeight()); //platform 32
    Enemy * spider2 = new Enemy();
    spider2->init(renderer, "./resources/images/spiderspritesheet.png", 4, 2, false, plat33->getW()/2, 3, 3);
    spider2->setPos((plat33->getX() + plat33->getW()/2) - spider2->getSpriteWidth()/2, plat33->getY() - spider2->getSpriteHeight());
    /* Creation of Enemies */

    //add to containter
    enemies.push_back(zombie);
    enemies.push_back(fireball);
    enemies.push_back(spider);
    enemies.push_back(zombie2);
    enemies.push_back(fireball1);
    enemies.push_back(fireball2);
    enemies.push_back(spider2);
    
    /* Creation of Items */
    Item * door = new Item();
    door->init(renderer, "./resources/images/door.jpg", 1, 1, 3, 3);
    door->setPos(plat19->getX() + plat19->getW() - door->getSpriteWidth(), plat19->getY() - door->getSpriteHeight());
    Item * heart = new Item();
    heart->init(renderer, "./resources/images/heart.png", 1, 1, 1, 1);
    heart->setPos((plat10->getX() + plat10->getW()/2) - heart->getSpriteWidth()/2, plat10->getY() - heart->getSpriteHeight());
    /* Creation of Items */
    
    //add to container
    items.push_back(door);
    items.push_back(heart);
    
    
}

void Map::createMap2(SDL_Renderer *renderer)
{
    /* Any platform/enemy/item that has a levelID == 1 will not be included in the second map */
    for (auto iter = platforms.begin(); iter != platforms.end(); ++iter)
    {
        if ((*iter)->getLevelID() == 1)
        {
            platforms.erase(iter);
            --iter;
        }
    }
    for (auto iter = enemies.begin(); iter != enemies.end(); ++iter)
    {
        if ((*iter)->getLevelID() == 1)
        {
            enemies.erase(iter);
            --iter;
        }
    }
    for (auto iter = items.begin(); iter != items.end(); ++iter)
    {
        if ((*iter)->getLevelID() == 1)
        {
            items.erase(iter);
            --iter;
        }
    }
    
    //Adding an item to the map
    Item * star = new Item();
    star->init(renderer, "./resources/images/star.png", 1, 1, 2, 2);
    star->setPos(400 + 400 - star->getSpriteWidth(), 645 - star->getSpriteHeight());
    items.push_back(star);
}

void Map::createMap3(SDL_Renderer *renderer)
{
    /* Any platform/enemy/item that has a levelID == 2 will not be included in the third map */
    
    for (auto iter = platforms.begin(); iter != platforms.end(); ++iter)
    {
        if ((*iter)->getLevelID() == 2)
        {
            platforms.erase(iter);
            --iter;
        }
    }
    for (auto iter = enemies.begin(); iter != enemies.end(); ++iter)
    {
        if ((*iter)->getLevelID() == 2)
        {
            enemies.erase(iter);
            --iter;
        }
    }
    for (auto iter = items.begin(); iter != items.end(); ++iter)
    {
        if ((*iter)->getLevelID() == 2)
        {
            items.erase(iter);
            --iter;
        }
    }
    
    //Adding an item to the map
    Item * heart = new Item();
    heart->init(renderer, "./resources/images/heart.png", 1, 1, 1, 3);
    heart->setPos((275 + 100/2) - heart->getSpriteWidth()/2, 450 - heart->getSpriteHeight());
    items.push_back(heart);
    
    //Adding an enemy to the map
    Enemy * fireball = new Enemy();
    fireball->init(renderer, "./resources/images/fireball.png", 1, 1, true, 50, 1, 3);
    fireball->setPos((825 + 75/2) - fireball->getSpriteWidth()/2, 255 - fireball->getSpriteHeight());
    enemies.push_back(fireball);
}

void Map::show(SDL_Renderer *renderer, float timeBetweenFrames)
{
    /* Handles all updates */
    
    if (_canShowMap && !_canCreateMap)
    {
        //render the background
        SDL_RenderCopy(renderer, _background, NULL, NULL);
        
        //render text
        _heroLivesText->renderText(renderer, 0, 0, 50, 50);
        
        //update & render hero
        _hero.update(timeBetweenFrames, platforms);
        _hero.render(renderer);
       
        //render platforms
        for (auto iter = platforms.begin(); iter != platforms.end(); ++iter)
        {
            (*iter)->show(renderer);
        }
        
        //update & render enemies
        for (auto iter = enemies.begin(); iter != enemies.end(); ++iter)
        {
            (*iter)->update(timeBetweenFrames);
            (*iter)->render(renderer);
            if (_hero.isInvincible())
            {
                static float frameCount = 0;
                frameCount += timeBetweenFrames;
                if (frameCount >= 80)
                {
                    _hero.loseInvincibility();
                    frameCount = 0;
                }
            }
            else
            {
                if (_hero.enemyCollision(**iter))
                {
                    _hero.reset(*platforms.at(0));
                }
            }
            
        }
        
        //render items
        for (auto iter = items.begin(); iter != items.end(); ++iter)
        {
            (*iter)->render(renderer);
            if (_hero.itemCollision(**iter))
            {
                switch ((*iter)->getID())
                {
                    /* If a collision is made with anything besides the door the item will disappear from the map */
                    case 1: items.erase(iter);
                            --iter;
                            break;
                    case 2: items.erase(iter);
                            --iter;
                            break;
                    default:
                        break;
                }
            }
        }
        
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        
        //update the text displaying the character's current lives
        std::stringstream ss;
        ss << "Lives: " << _hero.getLives();
        _heroLivesText->updateText(renderer, ss.str());
        
        if (_hero.completedLevel())
        {
            ++currentMap; //create the next map
            _hero.reset(*platforms.at(0));
            _canCreateMap = true; //allow creation of the next map
            _canShowMap = false; //do not allow the map to be shown until it's created
        }
    }
}

void Map::load(SDL_Renderer *renderer)
{
    if (_canCreateMap)
    {
        switch (currentMap)
        {
            case 1: createMap1(renderer); break;
            case 2: createMap2(renderer); break;
            case 3: createMap3(renderer); break;
            default: break;
        }
        _canCreateMap = false; //map is loaded
        _canShowMap = true; //allow map to be shown
    }
}

void Map::reset()
{
    //empty containers
    platforms.clear();
    enemies.clear();
    items.clear();
    
    //allow new map to be loaded
    _canCreateMap = true;
    //do not allow a map to be shown
    _canShowMap = false;
    //reset back to map 1
    currentMap = 1;
}

bool Map::shouldShowStartScreen(SDL_Renderer *renderer, float timeBetweenFrames)
{
    if (!_startScreen->getStart())
    {
        _startScreen->render(renderer, timeBetweenFrames);
        _canShowMap = false;
        return true;
    }
    return false;
}

bool Map::shouldShowLoseScreen(SDL_Renderer *renderer)
{
    if (_hero.getLives() == 0)
    {
        _loseScreen->render(renderer);
        if (_loseScreen->_playAgain())
        {
            _loseScreen->startNewGame(&_startScreen, _hero);
            reset();
        }
        return true;
    }
    return false;
}

bool Map::shouldShowWinScreen(SDL_Renderer *renderer)
{
    if (currentMap == 4)
    {
        _winScreen->render(renderer);
        if (_winScreen->_playAgain())
        {
            _winScreen->startNewGame(&_startScreen, _hero);
            reset();
        }
        return true;
    }
    return false;
}

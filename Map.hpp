#ifndef Map_hpp
#define Map_hpp

#include <stdio.h>
#include "header.h"

class Map
{
private:
    //std::vector<Platform>
    bool _changeMaps;
    Character *_hero;
public:
    Map();
    void loadMap1();
    void showMap1();
    void loadMap2();
    void loadMap3();
};

#endif /* Map_hpp */

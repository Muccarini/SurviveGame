#pragma once
#include "TileMap.h"
class Map 
{
public:

	virtual void draw(sf::RenderWindow * target) ;

	TileMap _tiles;
};


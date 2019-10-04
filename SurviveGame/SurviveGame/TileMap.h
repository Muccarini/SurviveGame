#pragma once
#include "Tile.h"
#include "Box2D/Box2D.h"

class TileMap
{
public:
	TileMap();
	virtual ~TileMap();

private:
	float grid_size_f;
	unsigned int grid_size_u;
	sf::Vector2f max_size;
	unsigned int layers;
	std::vector < std::vector < std::vector <Tile> > > map;//cordinate x,y e i layer z

public:
	void update();
	void render(sf::RenderTarget& target);
};


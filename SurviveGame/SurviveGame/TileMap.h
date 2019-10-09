#pragma once
#include "Tile.h"
#include "Box2D/Box2D.h"
#include <fstream>
#include <sstream>

class TileMap
{
public:
	TileMap();
	virtual ~TileMap();

private:
	float grid_size_f;
	sf::Vector2f max_size;
	unsigned int layers;
	int tile_type;

    std::vector< std::vector<Tile*> > map;
	sf::Texture tileset;

public:


	void loadFromFile(const std::string file_name);

	void render(sf::RenderTarget& target);
};


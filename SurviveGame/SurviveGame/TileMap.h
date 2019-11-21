#pragma once
#include "Tile.h"
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

	sf::RectangleShape wall;
	std::vector<sf::RectangleShape> walls;
	/*sf::RectangleShape creating_wall_block(std::vector<sf::RectangleShape> walls_rect);*/

	std::vector<sf::FloatRect> wall_block;



public:

	std::vector<sf::FloatRect> getWalls();

	void loadFromFile(const std::string file_name);

	void render(sf::RenderTarget& target);
};


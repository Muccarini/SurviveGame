#pragma once
#include "Tile.h"
#include <fstream>
#include <sstream>
#include "GridNode.h"

class TileMap
{
public:
	explicit TileMap(const sf::Vector2i map_size);
	virtual ~TileMap();

private:
	float grid_size_f;
	sf::Vector2i max_size;
	int tile_type;

    std::vector<std::vector<Tile*>> map;
	sf::Texture tileset;
		
	void loadFromFile(const std::string file_name);

public:

	void render(std::shared_ptr<sf::RenderTarget> target);

	std::vector<sf::FloatRect> findWalls(const int x, const int y) const;

	std::vector<GridLocation> getObstacle();
	
	float getGridSize();
};


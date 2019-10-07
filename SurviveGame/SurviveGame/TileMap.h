#pragma once
#include "Tile.h"
#include "Box2D/Box2D.h"
#include <fstream>

class TileMap : public sf::Drawable, sf::Transformable
{
public:
	TileMap();
	virtual ~TileMap();

private:
	float grid_size_f;
	unsigned int grid_size_u;
	sf::Vector2f max_size;
	unsigned int layers;
	sf::VertexArray tile_vertex;
	std::vector <Tile> map;
	sf::Texture tileset;

public:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void render(sf::RenderTarget& target);
};


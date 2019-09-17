#pragma once
#include "SFML/Graphics.hpp"

class TileMap : public sf::Drawable, sf::Transformable
{
public:

	TileMap(const int *level);
	virtual ~TileMap();

	bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles,
		unsigned int width, unsigned int height);

	//Functions
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


	std::vector<sf::RectangleShape> solidTiles;
	sf::RectangleShape collision;
	sf::FloatRect _col;

	const int * _level;
	int posMapX, posMapY;
private:
	//Attriburtes
	sf::VertexArray t_vertex;
	sf::Texture t_tileset;
	
};


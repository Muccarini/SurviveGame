#pragma once
#include "SFML/Graphics.hpp"

class TileMap1 : public sf::Drawable, sf::Transformable
{
public:

	TileMap1(const int *level);
	virtual ~TileMap1();

	bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles,
		unsigned int width, unsigned int height);

	//Functions
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


	//Attributes
	std::vector<sf::FloatRect> solidShapes;
	sf::RectangleShape _collision;
	sf::FloatRect _col;
	sf::FloatRect _windowSize;

	const int * _level;

private:
	//Attriburtes
	sf::VertexArray t_vertex;
	sf::Texture t_tileset;

};


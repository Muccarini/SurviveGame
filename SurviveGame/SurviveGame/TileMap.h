#pragma once
#include "SFML/Graphics.hpp"
struct Tile {

	sf::VertexArray t_vertex;
	int posMapX, posMapY;
	sf::RectangleShape collision;
	sf::FloatRect _col;

};


class TileMap : public sf::Drawable, sf::Transformable
{
public:

	TileMap(const int *level);
	virtual ~TileMap();

	bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles,
		unsigned int width, unsigned int height);

	//Functions
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::FloatRect findTile(sf::Vector2f posMap, sf::FloatRect spriteDim);


	//Attributes
	std::vector<sf::RectangleShape> solidTiles;
	sf::RectangleShape _collision;
	sf::FloatRect _col;

	const int * _level;
	int _posMapX, _posMapY;

	std::vector <Tile> _tiles;
	Tile _tile;

private:
	//Attriburtes
	sf::VertexArray t_vertex;
	sf::Texture t_tileset;
	


};


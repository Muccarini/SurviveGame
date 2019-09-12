#pragma once
#include "TileMap.h"
#include "Player.h"
#include <sstream>
class Map 
{
public:
	Map();
	virtual ~Map();

	virtual void draw();
	void update(sf::Time dt, sf::RenderWindow& target, Player* player);

	Player* _player;
	TileMap _tiles;
	sf::Text _text;
	sf::View _view;

private:
	sf::Font _font;

	//init game 
	float gridSizeF = 100.f;
	unsigned gridSizeU = static_cast<unsigned>(gridSizeF);
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2u mousePosGrid;
};


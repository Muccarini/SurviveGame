#pragma once
#include "TileMap.h"
#include "Player.h"
#include "Enemy.h"
#include "Observer.h"
#include <sstream>

class Map : public Observer
{
public:
	Map(Player* p, Enemy* e);
	virtual ~Map();

	virtual void draw();
	void update(sf::RenderWindow& target) override;

	virtual void attach() {};
	virtual void detach() {};


	Player* _player;
	Enemy* _enemy;
	TileMap _tileMap;
	//sf::Text _text;
	sf::View _view;

private:
	//sf::Font _font;
	float x, y;


	//init game 
	float gridSizeF = 100.f;
	unsigned gridSizeU = static_cast<unsigned>(gridSizeF);
	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2u mousePosGrid;
};


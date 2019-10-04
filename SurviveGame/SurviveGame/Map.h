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

	virtual void attach();
	virtual void detach();

	Player* _player;
	Enemy* _enemy;
	TileMap _tileMap;

private:
	float x, y;
};


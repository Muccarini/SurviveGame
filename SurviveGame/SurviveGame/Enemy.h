#pragma once
#include "Character.h"
#include "EnemyStrategyMove.h"

class Enemy :
	public Character
{

public:
	explicit Enemy(const std::shared_ptr<EntityData> entitydata);

	Enemy();
	virtual ~Enemy();

private:
	virtual void update();
	virtual void renderBullets(std::shared_ptr<sf::RenderWindow> target);

	void updateMove();
	void updateRotate();
	void updateHud();
	void updateCollision();

	void initVar();
	void initSprite();
	void initHitBox();

	void takeDamage(/*tipo di danno*/);

	float distance;
	float max_distance;
	std::list <sf::Vector2f> move_vect;
	sf::Vector2f target;
	sf::Vector2f spostamento;

	EnemyStrategyMove* _m;
	std::list<GridLocation> DIRS =
	{ GridLocation{4, 3}, GridLocation{16,4}, GridLocation{16, 3}, GridLocation{16, 5},
	  GridLocation{12, 6}, GridLocation{4, 6}, GridLocation{7, 6}, GridLocation{3, 12},
	  GridLocation{3, 13}, GridLocation{3, 14}, GridLocation{3, 15}, GridLocation{12, 12},
	  GridLocation{12, 13}, GridLocation{12, 14}, GridLocation{12, 15}, GridLocation{16, 15}};
};


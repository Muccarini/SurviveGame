#pragma once
#include "Character.h"
#include "EnemyStrategyMove.h"

class Enemy :
	public Character
{

public:
	Enemy();
	~Enemy();

private:
	void update(std::shared_ptr<EntityData> entitydata);

	void updateMove(sf::Time deltaTime, const std::shared_ptr<Character> target);
	void updateRotate(const std::shared_ptr<Character> target);
	void updateHud();

	void initVar();
	void initSprite();
	void initHitBox();

	void collisionWalls(std::vector<sf::FloatRect> walls);
	void collisionEnemies(std::vector<std::shared_ptr<Character>> enemies);

	EnemyStrategyMove _m;
};


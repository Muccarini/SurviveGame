#pragma once
#include "Character.h"
#include "EnemyStrategyMove.h"

class Enemy :
	public Character
{
public:
	enum Type {Ranged, Melee, Boss};

public:
	Enemy();
	~Enemy();

private:
	void update(std::shared_ptr<EntityData> entitydata);

	void updateMove(sf::Time deltaTime, const std::shared_ptr<Entity> target);
	void updateRotate(const std::shared_ptr<Entity> target);

	void collisionWalls(std::vector<sf::FloatRect> walls);
	void collisionEnemies(std::vector<std::shared_ptr<Entity>> enemies);

	void initSprite();
	void initHitBox();

	EnemyStrategyMove _m;
};


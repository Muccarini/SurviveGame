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

	EnemyStrategyMove _m;
};


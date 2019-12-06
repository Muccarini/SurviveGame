#pragma once
#include "Character.h"
#include "EnemyStrategyMove.h"

class Enemy :
	public Character
{

public:
	Enemy(sf::Texture textures_enemy);

	Enemy();
	virtual ~Enemy();

private:
	virtual void update(std::shared_ptr<EntityData> entitydata);
	virtual void renderBullets(std::shared_ptr<sf::RenderWindow> target);

	void updateMove(sf::Time deltaTime, const std::shared_ptr<Character> target);
	void updateRotate(const std::shared_ptr<Character> target);
	void updateHud();
	void updateCollision(std::shared_ptr<EntityData> entitydata);

	void initVar();
	void initSprite();
	void initHitBox();

	void takeDamage(/*tipo di danno*/);

	EnemyStrategyMove _m;
};


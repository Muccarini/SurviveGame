#pragma once
#include "GameCharacter.h"
#include "EnemyStrategyMove.h"

class Enemy :
	public GameCharacter
{
public:
	enum Type {Ranged, Melee, Boss};

public:
	Enemy(float x,float y);
	Enemy();

	virtual ~Enemy();

	 void move(sf::Time deltaTime);
	 void rotate(sf::Vector2f vec_dir);

	 void update(sf::Time deltaTime, GameCharacter * target);

private:
	EnemyStrategyMove _m;
	sf::Vector2f spawn_pos;
};


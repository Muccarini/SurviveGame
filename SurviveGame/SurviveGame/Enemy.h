#pragma once
#include "GameCharacter.h"
#include "EnemyStrategyMove.h"

class Enemy :
	public GameCharacter
{
public:
	enum Type {Ranged, Melee, Boss};

public:
	Enemy();
	virtual ~Enemy();

	 void move(sf::Time deltaTime)override;
	 void rotate(sf::Vector2f vec_dir)override;

	 //void update(sf::Time deltaTime, GameCharacter* target);

	 /*sf::Vector2f getPosition();*/

private:
	EnemyStrategyMove _m;
};


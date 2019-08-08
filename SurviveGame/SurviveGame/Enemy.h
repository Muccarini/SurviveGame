#pragma once
#include "GameCharacter.h"
#include "EnemyStrategyMove.h"
#include "Player.h"

class Enemy :
	public GameCharacter
{
public:
	enum Type {Ranged, Melee, Boss};

public:
	Enemy();
	virtual ~Enemy();

	 void move(sf::Time deltaTime);

	 void update(sf::Time deltaTime, Player* target);

private:
	EnemyStrategyMove _m;
	Animation _a;
};


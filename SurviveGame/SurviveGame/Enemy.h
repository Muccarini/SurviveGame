#pragma once
#include "GameCharacter.h"
#include "EnemyStrategyMove.h"


class Enemy :
	public GameCharacter
{
public:
	enum Type {Ranged, Melee, Boss};

public:
	explicit Enemy();
	virtual ~Enemy();

	virtual void move(sf::Time deltaTime);

	virtual void update(sf::Time deltaTime);

private:

	EnemyStrategyMove _m;
};


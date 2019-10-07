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

private:
	EnemyStrategyMove _m;
};


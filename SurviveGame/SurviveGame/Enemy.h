#pragma once
#include "GameCharacter.h"
#include "EnemyStrategyMove.h"

class Enemy :
	public GameCharacter
{
public:
	enum Type {Ranged, Melee, Boss};

public:
	Enemy(float x,float y, sf::Texture texture);
	Enemy();

	virtual ~Enemy();

	 void move(sf::Time deltaTime);
	 void rotate(sf::Vector2f vec_dir);

	 void update(sf::Time deltaTime, GameCharacter * target, std::vector<sf::FloatRect> collision, std::vector<std::shared_ptr<Enemy>> enemies);

	 void getDamage();

private:
	EnemyStrategyMove _m;
	sf::Vector2f spawn_pos;
	sf::Texture texture;
};


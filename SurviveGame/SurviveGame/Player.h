#pragma once
#include "GameCharacter.h"
#include "PlayerStrategyMove.h"

class Player :
	public GameCharacter
{
public:
	enum Type {Warrior, Ranger, Mage};
	
public:
	explicit Player();
	virtual ~Player();
	
	 void move(sf::Time deltaTime);

	 void update(sf::Time deltaTime);

	sf::Vector2f getPosition();


private:

	Type _type;
	PlayerStrategyMove _m;
};


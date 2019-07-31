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
	
	virtual void move(sf::Time deltaTime);

	virtual void update(sf::Time deltaTime);
	virtual void render(sf::RenderWindow* target);

private:

	Type _type;
	PlayerStrategyMove _m;
};


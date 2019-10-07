#pragma once
#include "GameCharacter.h"

class Player :
	public GameCharacter
{
public:
	enum Type {Warrior, Ranger, Mage};
	
public:
	Player();
	virtual ~Player();
	
	void move(sf::Time deltaTime) override;
	void rotate(sf::Vector2f mousePosView)override;

private:
	Type _type;
};


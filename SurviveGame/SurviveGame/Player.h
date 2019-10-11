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

	void update(sf::Time deltaTime, sf::Vector2f mousePosView, sf::FloatRect collision);

	bool Intersect(sf::CircleShape hit_box, sf::FloatRect collision);
	
	void move(sf::Time deltaTime, sf::FloatRect collision);
	void rotate(sf::Vector2f mousePosView);

private:
	Type _type;
};


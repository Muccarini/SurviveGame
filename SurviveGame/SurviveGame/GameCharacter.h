#pragma once
#include "TextureHolder.h"
#include "StrategyMove.h"

class GameCharacter
{
public:
	enum Type {Warrior, Ranger, Mage};
	
public:
	explicit GameCharacter();
	
	void move(sf::Time deltaTime);

	void update(sf::Time deltaTime);
	void render(sf::RenderWindow* target);

private:
	Type _type;

	sf::Sprite _sprite;
	TextureHolder _textures;

    float _movementSpeed = 200.f;

	StrategyMove _m;
};


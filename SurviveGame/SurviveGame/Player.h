#pragma once
#include "TextureHolder.h"
#include "StrategyMove.h"
#include "GameCharacter.h"

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

protected:
	Type _type;

	sf::Sprite _sprite;
	TextureHolder _textures;

    float _movementSpeed = 200.f;

	StrategyMove _m;
};


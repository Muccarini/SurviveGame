#pragma once
#include "Entity.h"
#include "StrategyMove.h"

class GameCharacter :
	public Entity , public sf::Sprite
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
	StrategyMove _m;

	float _movementSpeed = 200.f;
};


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
	
	void move(sf::Time deltaTime, sf::Sprite _sprite) ;

	void update(sf::Time deltaTime, sf::Sprite _sprite);
	void render(sf::RenderWindow* target) ;

	sf::Sprite _sprite;
private:
	Type _type;

	TextureHolder _textures;
	StrategyMove _m;

	float _movementSpeed = 200.f;
};


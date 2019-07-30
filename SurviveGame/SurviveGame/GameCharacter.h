#pragma once
#include "Entity.h"

class GameCharacter :
	public Entity
{
public:
	enum Type {Warrior, Ranger, Mage};
public:
	explicit GameCharacter();
	
	void move(sf::Time deltaTime, const float dir_x, const float dir_y) ;

	void update(sf::Time deltaTime) ;
	void render(sf::RenderWindow* target) ;

	bool isMoving();
	void setMoving(bool moving);


private:
	Type _type;

	sf::Sprite _sprite;
	TextureHolder _textures;

	bool _moving;

	float _movementSpeed = 200.f;
};


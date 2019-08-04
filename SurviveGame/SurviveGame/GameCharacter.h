#pragma once
#include"SFML/Graphics.hpp"
#include"TextureHolder.h"

class GameCharacter
{
public:
	GameCharacter();
	virtual ~GameCharacter();

	void render(sf::RenderWindow* target);
	


protected:

	sf::Sprite _sprite;
	TextureHolder _textures;

	float _movementSpeed;


};


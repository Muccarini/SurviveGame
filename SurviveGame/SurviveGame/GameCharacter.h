#pragma once
#include"SFML/Graphics.hpp"
#include"TextureHolder.h"
#include "Subject.h"

class GameCharacter : public Subject
{
public:
	GameCharacter();
	virtual ~GameCharacter();

	void render(sf::RenderWindow* target);
	float _movementSpeed;

protected:

	sf::Sprite _sprite;
	TextureHolder _textures;

	sf::FloatRect _colBox;

};


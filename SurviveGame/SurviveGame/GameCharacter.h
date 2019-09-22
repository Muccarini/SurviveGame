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
	sf::Vector2f _oldPos;
	float _movementSpeed;

	sf::FloatRect _colBox;
	sf::RectangleShape _sprShape;


	sf::Sprite _sprite;
protected:

	TextureHolder _textures;
};


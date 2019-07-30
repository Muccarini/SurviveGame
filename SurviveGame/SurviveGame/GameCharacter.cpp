#include "GameCharacter.h"


GameCharacter::GameCharacter()
{
	_textures.load(Textures::Personaggio, "Sources/Sprite_laila_run2.png");
	_sprite.setTexture(_textures.get(Textures::Personaggio));
	_sprite.setPosition(100.f, 100.f);
	_sprite.setTextureRect(sf::IntRect(0, 0, 32, 48));
}

void GameCharacter::move(sf::Time deltaTime,const float dir_x,const float dir_y)
{
	_sprite.move(dir_x * deltaTime.asSeconds() * _movementSpeed, dir_y * deltaTime.asSeconds() *_movementSpeed);
}

void GameCharacter::update(sf::Time deltaTime) 
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		move(deltaTime, 0.f, -1.f);
		_sprite.setTextureRect(sf::IntRect(0 * 32, 48, 32, 48));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		move(deltaTime, -1.f, 0.f);
		_sprite.setTextureRect(sf::IntRect(0 * 32, 48 *2, 32, 48));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		move(deltaTime, 0.f, 1.f);
		_sprite.setTextureRect(sf::IntRect(0 * 32, 0, 32, 48));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		move(deltaTime, 1.f, 0.f);
		_sprite.setTextureRect(sf::IntRect(0 * 32, 48 * 3, 32, 48));
	}
}

void GameCharacter::render(sf::RenderWindow* target)
{
	target->draw(_sprite);
}

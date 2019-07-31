#include "Player.h"


Player::Player()
{
	_textures.load(Textures::Personaggio, "Sources/Sprite_laila_run2.png");
	_sprite.setTexture(_textures.get(Textures::Personaggio));
	_sprite.setPosition(100.f, 100.f);
	_sprite.setTextureRect(sf::IntRect(0, 0, 32, 48));
}

Player::~Player()
{
}

void Player::move(sf::Time deltaTime)
{
	//_sprite.move(dir_x * deltaTime.asSeconds() * _movementSpeed, dir_y * deltaTime.asSeconds() *_movementSpeed);
	this->_m.move(deltaTime, _sprite, _movementSpeed);
}

void Player::update(sf::Time deltaTime)
{
		move(deltaTime);
		
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
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
	}*/
}
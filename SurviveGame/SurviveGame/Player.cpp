#include "Player.h"


Player::Player()
{
	_movementSpeed = 200;
	_textures.load(Textures::Personaggio, "Sources/Top_Down_Survivor/rifle/move/survivor-move_rifle_0.png");
	_sprite.setTexture(_textures.get(Textures::Personaggio));
	_sprite.setScale(0.4, 0.4);
	_sprite.setPosition(100.f, 100.f);
	       // IL PUNTO DI ROTAZIONE NON E' CENTRATO //
		   // non so se e' 5, 5
	_sprite.setOrigin(_sprite.getPosition().x +5, _sprite.getPosition().y +5);
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



		float dX = sf::Mouse::getPosition().x - this->_sprite.getPosition().x;
		float dY = sf::Mouse::getPosition().y - this->_sprite.getPosition().y;

		const float PI = 3.14159265f;
		float deg = atan2(dY, dX) * 180.f / PI;

		this->_sprite.setRotation(deg + 90.f * _sens);
}

sf::Vector2f Player::getPosition()
{
	return
		this->_sprite.getPosition();
}

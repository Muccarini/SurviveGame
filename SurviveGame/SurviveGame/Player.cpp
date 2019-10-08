#include "Player.h"


Player::Player()
{
	mov_speed = 200;
	_textures.load(Textures::Personaggio, "Sources/Top_Down_Survivor/rifle/move/survivor-move_rifle_0.png");
	_sprite.setTexture(_textures.get(Textures::Personaggio));
	_sprite.setScale(0.1f, 0.1f);
	_sprite.setPosition(150.f, 150.f);
	_sprite.setOrigin(105, 105);
}

Player::~Player()
{
}

void Player::move(sf::Time deltaTime) // TODO// cambiare mov_speed in movSpeed
	{
		sf::Vector2f vectorMov(0.f, 0.f);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			vectorMov.x = 0.f;
			vectorMov.y = 0.f;
			vectorMov.y = -mov_speed;
			_sprite.move(vectorMov* deltaTime.asSeconds());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			vectorMov.x = 0.f;
			vectorMov.y = 0.f;
			vectorMov.x = -mov_speed;
			_sprite.move(vectorMov * deltaTime.asSeconds());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			vectorMov.x = 0.f;
			vectorMov.y = 0.f;
			vectorMov.y = mov_speed;
			_sprite.move(vectorMov * deltaTime.asSeconds());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			vectorMov.x = 0.f;
			vectorMov.y = 0.f;
			vectorMov.x = mov_speed;
			_sprite.move(vectorMov * deltaTime.asSeconds());
		}
	}

void Player::rotate(sf::Vector2f mousePosView)
{
	float dX = mousePosView.x - getPosition().x;
	float dY = mousePosView.y - getPosition().y;
	const float PI = 3.14159265f;
	float deg = atan2(dY, dX) * 180.f / PI;

	this->_sprite.setRotation(deg + 360.f);
}

void Player::update(sf::Time deltaTime, sf::Vector2f mousePosView)
{
	move(deltaTime);
	rotate(mousePosView);
}


#include "Player.h"


Player::Player()
{
	mov_speed = 200;
	_textures.load(Textures::Personaggio, "Sources/Top_Down_Survivor/rifle/move/survivor-move_rifle_0.png");
	_sprite.setTexture(_textures.get(Textures::Personaggio));
	hit_box.setRadius(_sprite.getGlobalBounds().width /3.f);
	hit_box.setOutlineColor(sf::Color::Magenta);
	hit_box.setOutlineThickness(3.f);
	hit_box.setFillColor(sf::Color::Transparent);
	_sprite.setScale(0.3f, 0.3f);
	hit_box.setScale(_sprite.getScale());
	_sprite.setPosition(300.f, 300.f);
	hit_box.setPosition(getPosition());
	_sprite.setOrigin(90, 110);
	hit_box.setOrigin(_sprite.getOrigin());

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

void Player::update(sf::Time deltaTime, sf::Vector2f mousePosView, sf::FloatRect collision)
{
	if (!hit_box.getGlobalBounds().intersects(collision))
	{
		move(deltaTime);
		hit_box.setPosition(getPosition());
	}

	rotate(mousePosView);
	hit_box.setRotation(_sprite.getRotation());
	

}


#include "PlayerStrategyMove.h"



PlayerStrategyMove::PlayerStrategyMove()
{
}


PlayerStrategyMove::~PlayerStrategyMove()
{
}


void PlayerStrategyMove::move(sf::Time deltaTime, sf::Sprite & _sprite, const float mov_speed) // TODO// cambiare mov_speed in movSpeed
{	
	sf::Vector2f vectorMov(0.f, 0.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (_sprite.getPosition().y > 0.f) {
			vectorMov.x = 0.f;
			vectorMov.y = 0.f;
			vectorMov.y = -mov_speed;
			_sprite.move(vectorMov* deltaTime.asSeconds());
			//_sprite.setTextureRect(sf::IntRect(0 * 32, 48, 32, 48));
		}
		else _sprite.setPosition(_sprite.getPosition().x, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (_sprite.getPosition().y < 1080.f) {
			vectorMov.x = 0.f;
			vectorMov.y = 0.f;
			vectorMov.y = mov_speed;
			_sprite.move(vectorMov * deltaTime.asSeconds());
			//_sprite.setTextureRect(sf::IntRect(0 * 32, 0, 32, 48));
		}
		else _sprite.setPosition(_sprite.getPosition().x, 1080.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (_sprite.getPosition().x > 0.f) {
			vectorMov.x = 0.f;
			vectorMov.y = 0.f;
			vectorMov.x = -mov_speed;
			_sprite.move(vectorMov * deltaTime.asSeconds());
			//_sprite.setTextureRect(sf::IntRect(0 * 32, 48 * 2, 32, 48));
		}
		else _sprite.setPosition(0.f, _sprite.getPosition().y);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (_sprite.getPosition().x < 1920.f){
		vectorMov.x = 0.f;
		vectorMov.y = 0.f;
		vectorMov.x = mov_speed;
		_sprite.move(vectorMov * deltaTime.asSeconds());
		//_sprite.setTextureRect(sf::IntRect(0 * 32, 48 * 3, 32, 48));
		}
		else _sprite.setPosition(1920.f, _sprite.getPosition().y);
	}
}

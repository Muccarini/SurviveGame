#include "PlayerStrategyMove.h"



PlayerStrategyMove::PlayerStrategyMove()
{
}


PlayerStrategyMove::~PlayerStrategyMove()
{
}


void PlayerStrategyMove::move (sf::Time deltaTime, sf::Sprite & _sprite, const float mov_speed) // TODO// cambiare mov_speed in movSpeed
{	
	sf::Vector2f vectorMov(0.f, 0.f);
	/*if (_sprite.getGlobalBounds().left > 0.f &&
		_sprite.getGlobalBounds().left + _sprite.getGlobalBounds().width > 0.f &&
		_sprite.getGlobalBounds().top > 0.f &&
		_sprite.getGlobalBounds().top + _sprite.getGlobalBounds().height > 0.f
		||
		_sprite.getGlobalBounds().left < 1080.f &&
		_sprite.getGlobalBounds().left + _sprite.getGlobalBounds().width < 1080.f &&
		_sprite.getGlobalBounds().top < 1080.f &&
		_sprite.getGlobalBounds().top + _sprite.getGlobalBounds().height < 1080.f
		||
		_sprite.getGlobalBounds().left < 1920.f &&
		_sprite.getGlobalBounds().left + _sprite.getGlobalBounds().width < 1920.f &&
		_sprite.getGlobalBounds().top < 1920.f &&
		_sprite.getGlobalBounds().top + _sprite.getGlobalBounds().height < 1920.f
		)*/
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			/*if (_sprite.getGlobalBounds().left > 0.f &&
				_sprite.getGlobalBounds().left + _sprite.getGlobalBounds().width > 0.f &&
				_sprite.getGlobalBounds().top > 0.f &&
				_sprite.getGlobalBounds().top + _sprite.getGlobalBounds().height > 0.f) {*/
				vectorMov.x = 0.f;
				vectorMov.y = 0.f;
				vectorMov.y = -mov_speed;
				_sprite.move(vectorMov* deltaTime.asSeconds());
				//_sprite.setTextureRect(sf::IntRect(0 * 32, 48, 32, 48));
			/*}
			else _sprite.setPosition(_sprite.getPosition());*/
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			/*if (_sprite.getGlobalBounds().left < 1080.f &&
				_sprite.getGlobalBounds().left + _sprite.getGlobalBounds().width < 1080.f &&
				_sprite.getGlobalBounds().top < 1080.f &&
				_sprite.getGlobalBounds().top + _sprite.getGlobalBounds().height < 1080.f) {*/
				vectorMov.x = 0.f;
				vectorMov.y = 0.f;
				vectorMov.y = mov_speed;
				_sprite.move(vectorMov * deltaTime.asSeconds());
				//_sprite.setTextureRect(sf::IntRect(0 * 32, 0, 32, 48));
			/*}
			else _sprite.setPosition(_sprite.getPosition());*/
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			/*if (_sprite.getGlobalBounds().left > 0.f &&
				_sprite.getGlobalBounds().left + _sprite.getGlobalBounds().width > 0.f &&
				_sprite.getGlobalBounds().top > 0.f &&
				_sprite.getGlobalBounds().top + _sprite.getGlobalBounds().height > 0.f) {*/
				vectorMov.x = 0.f;
				vectorMov.y = 0.f;
				vectorMov.x = -mov_speed;
				_sprite.move(vectorMov * deltaTime.asSeconds());
				//_sprite.setTextureRect(sf::IntRect(0 * 32, 48 * 2, 32, 48));
			/*}
			else _sprite.setPosition(_sprite.getPosition());*/
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			/*if (_sprite.getGlobalBounds().left < 1920.f &&
				_sprite.getGlobalBounds().left + _sprite.getGlobalBounds().width < 1920.f &&
				_sprite.getGlobalBounds().top < 1920.f &&
				_sprite.getGlobalBounds().top + _sprite.getGlobalBounds().height < 1920.f) {*/
				vectorMov.x = 0.f;
				vectorMov.y = 0.f;
				vectorMov.x = mov_speed;
				_sprite.move(vectorMov * deltaTime.asSeconds());
				//_sprite.setTextureRect(sf::IntRect(0 * 32, 48 * 3, 32, 48));
			/*}
			else _sprite.setPosition(_sprite.getPosition());*/
		}
	}
}

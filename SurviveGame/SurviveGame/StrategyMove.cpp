#include "StrategyMove.h"
#include "Game.h"

StrategyMove::~StrategyMove()
{
}

void StrategyMove::move(sf::Time deltatime, sf::Sprite& _sprite, const float mov_speed)
{
	sf::Vector2f vector(0.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		vector.x = 0.f;
		vector.y = 0.f;
		vector.y = -mov_speed;
		(_sprite).move( vector* deltatime.asSeconds());
		(_sprite).setTextureRect(sf::IntRect(0 * 32, 48, 32, 48));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		vector.x = 0.f;
		vector.y = 0.f;
		vector.x = -mov_speed;
		(_sprite).move(vector * deltatime.asSeconds());
		(_sprite).setTextureRect(sf::IntRect(0 * 32, 48 * 2, 32, 48));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		vector.x = 0.f;
		vector.y = 0.f;
		vector.y = mov_speed;
		(_sprite).move(vector * deltatime.asSeconds());
		(_sprite).setTextureRect(sf::IntRect(0 * 32, 0, 32, 48));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		vector.x = 0.f;
		vector.y = 0.f;
		vector.x = mov_speed;
		(_sprite).move(vector * deltatime.asSeconds());
		(_sprite).setTextureRect(sf::IntRect(0 * 32, 48 * 3, 32, 48));
	}
	
}




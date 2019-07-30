#include "StrategyMove.h"



StrategyMove::StrategyMove()
{
}

void StrategyMove::MoveS(sf::Time deltaTime, sf::Sprite _player, float _m_s)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		_player.move(0 * deltaTime.asSeconds() * _m_s, 1 * deltaTime.asSeconds() * _m_s);
		//_sprite.setTextureRect(sf::IntRect(0 * 32, 48, 32, 48));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		_player.move(-1 * deltaTime.asSeconds() * _m_s, 0 * deltaTime.asSeconds() * _m_s);
		//_sprite.setTextureRect(sf::IntRect(0 * 32, 48 * 2, 32, 48));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		_player.move(1 * deltaTime.asSeconds() * _m_s, 0 * deltaTime.asSeconds() * _m_s);
		//_sprite.setTextureRect(sf::IntRect(0 * 32, 0, 32, 48));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		_player.move(0 * deltaTime.asSeconds() * _m_s, -1 * deltaTime.asSeconds() * _m_s);
		//_sprite.setTextureRect(sf::IntRect(0 * 32, 48 * 3, 32, 48));
	}
}

StrategyMove::~StrategyMove()
{
}

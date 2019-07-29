#include "StrategyMove.h"

StrategyMove::~StrategyMove()
{
}

sf::Vector2f& StrategyMove::MoveS(const sf::Vector2f &position, sf::Sprite _character)
{
	const float PlayerSpeed = 150.f;
	sf::Vector2f offset = position;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		offset.y -= PlayerSpeed;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		offset.x -= PlayerSpeed;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		offset.y += PlayerSpeed;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		offset.x += PlayerSpeed;
	return offset;
	
}




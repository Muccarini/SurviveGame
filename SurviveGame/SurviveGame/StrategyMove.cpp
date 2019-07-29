#include "StrategyMove.h"

StrategyMove::~StrategyMove()
{
}

sf::Vector2f StrategyMove::MoveS(sf::Vector2f* movement, sf::Sprite _character)
{
	const float PlayerSpeed = 150.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		movement->y -= PlayerSpeed;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		movement->x -= PlayerSpeed;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		movement->y += PlayerSpeed;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		movement->x += PlayerSpeed;
	_character.move(movement);
	
}




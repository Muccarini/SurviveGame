#include "StrategyMove.h"

StrategyMove::~StrategyMove()
{
}

sf::Vector2f StrategyMove::MoveS(const sf::Vector2f* movement, sf::Sprite _character)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		*movement.y = sf::Vector2f(0, -1);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		*movement = sf::Vector2f(-1, 0);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		*movement = sf::Vector2f(0, -1);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	    *movement = sf::Vector2f(1, 0);
	_character.move(movement);
	
}




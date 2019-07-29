#pragma once
#include "SFML/Graphics.hpp"
class StrategyMove
{
public:

	virtual ~StrategyMove();

	sf::Vector2f MoveS(const sf::Vector2f * movement, sf::Sprite _character);
	sf::Sprite _character;
};


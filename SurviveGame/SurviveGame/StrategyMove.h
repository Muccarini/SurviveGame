#pragma once
#include "SFML/Graphics.hpp"
class StrategyMove
{
public:
	StrategyMove();
	void MoveS(sf::Time deltaTime, sf::Sprite _player, float _m_s);
	~StrategyMove();
	
};


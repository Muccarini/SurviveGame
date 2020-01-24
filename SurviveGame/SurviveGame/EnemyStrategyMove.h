#pragma once
#include "StrategyMove.h"
#include "GridNode.h"
#include <unordered_map>

class EnemyStrategyMove :
	public StrategyMove
{
public:
	virtual ~EnemyStrategyMove();

	void move(sf::Time deltatime, sf::Sprite& _sprite,const float mov_speed) override;

	bool pathFinder(GridNode grid, GridLocation start, GridLocation goal, 
		std::unordered_map<GridLocation, GridLocation>& came_from,
		std::unordered_map<GridLocation, double>& cost_so_far);
};


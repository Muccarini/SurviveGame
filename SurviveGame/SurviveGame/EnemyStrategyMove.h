#pragma once
#include "StrategyMove.h"
#include "GridNode.h"
#include <unordered_map>
#include <functional>
#include <utility>

class EnemyStrategyMove :
	public StrategyMove
{
public:
	EnemyStrategyMove(GridNode grid);
	virtual ~EnemyStrategyMove();

	void move(sf::Time deltatime, sf::Sprite& _sprite, sf::Vector2f target,
		std::list<sf::Vector2f> &movevect, const float mov_speed) override;
private:
	void a_star_search(GridNode graph, GridLocation start, GridLocation goal,
		std::unordered_map<GridLocation, GridLocation>& came_from,
		std::unordered_map<GridLocation, double>& cost_so_far, std::list<sf::Vector2f> &movevect);
	std::vector<GridLocation> reconstruct_path(GridLocation start, GridLocation goal,
		std::unordered_map<GridLocation, GridLocation> came_from);

protected:
	std::unordered_map<GridLocation, GridLocation> came_from;
	std::unordered_map<GridLocation, double> cost_so_far;
	GridLocation start;
	GridLocation goal;
	GridNode grid; 
};





#include "EnemyStrategyMove.h"

inline double heuristic(GridLocation a, GridLocation b) 
{
	return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}


EnemyStrategyMove::EnemyStrategyMove(GridNode grid) : grid(grid)
{

}

EnemyStrategyMove::~EnemyStrategyMove()
{
}

void EnemyStrategyMove::move(sf::Time deltatime, sf::Sprite & _sprite, sf::Vector2f target, std::list<sf::Vector2i> &movevect)
{
	this->start = { static_cast<int>(_sprite.getPosition().x / 64) , static_cast<int>(_sprite.getPosition().y / 64) };
	this->goal = { static_cast<int>(target.x / 64) , static_cast<int>(target.y / 64) };
	a_star_search(this->grid, this->start, this->goal, this->came_from, this->cost_so_far, movevect);
	this->came_from.clear();
	this->cost_so_far.clear();
}
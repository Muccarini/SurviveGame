#include "EnemyStrategyMove.h"

//#include <C:/Users/Federico/source/Repos/SurviveGame/SurviveGame/SurviveGame/implementation.cpp>

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

void EnemyStrategyMove::move(sf::Time deltatime, sf::Sprite & _sprite, sf::Vector2f target)
{
	this->start = { static_cast<int>(_sprite.getPosition().x / 64) , static_cast<int>(_sprite.getPosition().y / 64) };
	this->goal = { static_cast<int>(target.x / 64) , static_cast<int>(target.y / 64) };
	a_star_search(this->grid, this->start, this->goal, this->came_from, this->cost_so_far);
}

//bool EnemyStrategyMove::pathFinder(GridNode grid, GridLocation start, 
//	GridLocation goal, std::unordered_map<GridLocation, GridLocation>& came_from,
//	std::unordered_map<GridLocation, double>& cost_so_far)
//{
//	
//  PriorityQueue<GridLocation, double> frontier;
//  /*frontier.put(start, 0);*/
//
//  came_from[start] = start;
//  cost_so_far[start] = 0;
//  
//  while (!frontier.empty()) {
//	GridLocation current = frontier.get();
//
//    if (current.isEqual(goal)) {
//      return true;
//    }
//
//    for (GridLocation next : grid.neighbors(current)) {
//      double new_cost = cost_so_far[current] + grid.cost(current, next);
//      if (cost_so_far.find(next) == cost_so_far.end()
//          || new_cost < cost_so_far[next]) {
//        cost_so_far[next] = new_cost;
//        double priority = new_cost + heuristic(next, goal);
//        frontier.put(next, priority);
//        came_from[next] = current;
//      }
//    }
//  }
//
//  return false;
//
//}

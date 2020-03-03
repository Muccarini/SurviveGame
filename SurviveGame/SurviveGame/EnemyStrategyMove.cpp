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

void EnemyStrategyMove::move(sf::Time deltatime, sf::Sprite& _sprite, sf::Vector2f target,
	std::list<sf::Vector2f> &movevect, const float mov_speed)
{
	this->start = { static_cast<int>(_sprite.getPosition().x / 64) , static_cast<int>(_sprite.getPosition().y / 64) };
	this->goal = { static_cast<int>(target.x / 64) , static_cast<int>(target.y / 64) };
	a_star_search(this->grid, this->start, this->goal, this->came_from, this->cost_so_far, movevect);
	this->came_from.clear();
	this->cost_so_far.clear();
}

void EnemyStrategyMove::a_star_search(GridNode graph, GridLocation start, GridLocation goal, std::unordered_map<GridLocation, GridLocation>& came_from, std::unordered_map<GridLocation, double>& cost_so_far, std::list<sf::Vector2f>& movevect)
{
	PriorityQueue<GridLocation, double> frontier;
	frontier.put(start, 0);

	came_from[start] = start;
	cost_so_far[start] = 0;

	while (!frontier.empty()) {
		GridLocation current = frontier.get();

		if (current == goal)
		{
			break;
		}

		for (GridLocation next : graph.neighbors(current))
		{
			double new_cost = cost_so_far[current] + graph.cost(current, next);
			if (cost_so_far.find(next) == cost_so_far.end()
				|| new_cost < cost_so_far[next]) {
				cost_so_far[next] = new_cost;
				double priority = new_cost + heuristic(next, goal);
				frontier.put(next, priority);
				came_from[next] = current;
			}
		}
	}

	std::vector<GridLocation> path = reconstruct_path(start, goal, came_from);

	for (unsigned int i = 0; i < path.size() - 1; i++)
	{
		sf::Vector2f move = sf::Vector2f(path[i].x - path[i + 1].x,
			path[i].y - path[i + 1].y);
		movevect.push_back(-move);
	}
}

std::vector<GridLocation> EnemyStrategyMove::reconstruct_path(GridLocation start, GridLocation goal, std::unordered_map<GridLocation, GridLocation> came_from)
{

	std::vector<GridLocation> path;
	GridLocation current = goal;
	while (current != start) {
		path.push_back(current);
		current = came_from[current];
	}
	path.push_back(start); // per evitare errori quando sono nella stessa posizione
	std::reverse(path.begin(), path.end());
	return path;
}


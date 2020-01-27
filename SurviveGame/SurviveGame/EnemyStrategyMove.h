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

	void move(sf::Time deltatime, sf::Sprite& _sprite, sf::Vector2f target, std::list<sf::Vector2i> &movevect);

protected:
	std::unordered_map<GridLocation, GridLocation> came_from;
	std::unordered_map<GridLocation, double> cost_so_far;
	GridLocation start{ 1, 4 };
	GridLocation goal{ 8, 5 };
	GridNode grid;
};

template<typename Location, typename Graph>
void a_star_search
(	Graph graph,
	Location start,
	Location goal,
	std::unordered_map<Location, Location>& came_from,
	std::unordered_map<Location, double>& cost_so_far, std::list<sf::Vector2i> &movevect)
{
	PriorityQueue<Location, double> frontier;
	frontier.put(start, 0);

	came_from[start] = start;
	cost_so_far[start] = 0;

	while (!frontier.empty()) {
		Location current = frontier.get();

		if (current == goal) {
			break;
		}

		for (Location next : graph.neighbors(current)) 
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

	for (int i = 0; i < path.size(); i++)
	{
		sf::Vector2i move = sf::Vector2i(path.back().x / path.back().x, 
			path.back().y / path.back().y);
		movevect.push_back(move);
		std::cout << "{ " << path[i].x << ", " << path[i].y << "}";
	}

}


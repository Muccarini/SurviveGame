#pragma once
#include "GridNode.h"
#include "SFML/Graphics.hpp"
#include <unordered_map>
#include <functional>
#include <utility>

class AStar
{
public:
	AStar(const GridNode& grid,const float max_d);
	AStar();

	virtual ~AStar();

	sf::Vector2f const move(const sf::Time& deltatime, const sf::Vector2f subject, const sf::Vector2f target,
		std::list<sf::Vector2f> &movevect, const float mov_speed);

	void setMaxDist(float m_distance);

private:
	void a_star_search(const GridNode& graph, GridLocation start, GridLocation goal,
		std::unordered_map<GridLocation, GridLocation>& came_from,
		std::unordered_map<GridLocation, double>& cost_so_far, std::list<sf::Vector2f> &movevect);

	    std::vector<GridLocation> reconstruct_path(GridLocation start, GridLocation goal,
		std::unordered_map<GridLocation, GridLocation> came_from);

protected:
	GridNode grid; 

	float max_distance;

	sf::Vector2f target;
	sf::Vector2f spostamento;
};





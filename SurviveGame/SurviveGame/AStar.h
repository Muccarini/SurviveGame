#pragma once
#include "GridNode.h"
#include "SFML/Graphics.hpp"
#include <unordered_map>
#include <functional>
#include <utility>

class AStar
{
public:
	AStar(GridNode grid, float max_d, float dist);
	AStar();

	virtual ~AStar();

	sf::Vector2f move(sf::Time deltatime, sf::Sprite* _sprite, sf::Vector2f target,
		std::list<sf::Vector2f> &movevect, const float mov_speed);
	void setMaxDist(float m_distance);
	void setDist(float dist);
	void setTarget(sf::Vector2f target);
private:
	void a_star_search(GridNode graph, GridLocation start, GridLocation goal,
		std::unordered_map<GridLocation, GridLocation>& came_from,
		std::unordered_map<GridLocation, double>& cost_so_far, std::list<sf::Vector2f> &movevect);
	std::vector<GridLocation> reconstruct_path(GridLocation start, GridLocation goal,
		std::unordered_map<GridLocation, GridLocation> came_from);

protected:
	std::unordered_map<GridLocation, GridLocation> came_from;
	std::unordered_map<GridLocation, double> cost_so_far;
	GridNode grid; 
	float max_distance;
	float distance;
	sf::Vector2f target;
	sf::Vector2f spostamento;
};





#pragma once
#include "Character.h"
#include "Astar.h"

class Boss :
	public Character
{
public:
	explicit Boss(GridNode grid, sf::Texture texture);
	Boss();

	virtual ~Boss();

	void updateMove(sf::Time deltaTime, sf::Vector2f target, float grid_size);
	bool shooting(sf::Time deltaTime, sf::Vector2f target);
	void updateRotate(sf::Vector2f target);
	void updateReload(sf::Time deltaTime);
	void updateHud();
	void updateCollision(sf::FloatRect player, std::vector<sf::FloatRect> walls, float grid_size);

private:

	bool isInRange(sf::Vector2f obj1, sf::Vector2f obj2);

	void initVar();
	void initSprite(GridNode grid, sf::Texture texture);
	void initHitBox();

	float distance;
	float max_distance;
	std::list <sf::Vector2f> move_vect;
	sf::Vector2f spostamento;

	AStar _m;
};


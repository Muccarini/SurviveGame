#pragma once
#include "Character.h"
#include "AStar.h"

class Enemy :
	public Character
{

public:
	explicit Enemy(const sf::Texture& texture, const GridNode& grid, float grid_size);
	Enemy();
	virtual ~Enemy();

	void updateMove(sf::Time deltaTime, sf::Vector2f target, float grid_size);
	void updateRotate(sf::Vector2f target);
	void updateHud();

private:
	void initVar();
	void initSprite(GridNode grid,const sf::Texture & texture);
	void initHitBox(float grid_size); 

	const float max_distance = 64; //check tile

	std::list <sf::Vector2f> move_vect;

	AStar _m;
};


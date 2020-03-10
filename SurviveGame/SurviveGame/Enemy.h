#pragma once

#include "Character.h"
#include "AStar.h"

class Character;
class PlayerT;
class Pet;

class Enemy :
	public Character
{

public:
	explicit Enemy(const sf::Texture& texture, GridNode grid, float grid_size);

	Enemy();
	virtual ~Enemy();

	void updateMove(sf::Time deltaTime, sf::Vector2f target, float grid_size);
	void updateRotate(sf::Vector2f target);
	void updateHud();
	void updateCollision(std::shared_ptr<Character> player, std::shared_ptr<Character> pet, std::vector<sf::FloatRect> walls, float grid_size);

private:
	void initVar();
	void initSprite(GridNode grid,const sf::Texture & texture);
	void initHitBox(float grid_size); 

	float distance;
	float max_distance;
	std::list <sf::Vector2f> move_vect;
	sf::Vector2f target;
	sf::Vector2f spostamento;

	AStar _m;

	std::list<GridLocation> DIRS =
	{ GridLocation{4, 3}, GridLocation{16,4}, GridLocation{16, 3}, GridLocation{16, 5},
	  GridLocation{12, 6}, GridLocation{4, 6}, GridLocation{7, 6}, GridLocation{3, 12},
	  GridLocation{3, 13}, GridLocation{3, 14}, GridLocation{3, 15}, GridLocation{12, 12},
	  GridLocation{12, 13}, GridLocation{12, 14}, GridLocation{12, 15}, GridLocation{16, 15}};
};


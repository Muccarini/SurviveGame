#pragma once
#include "Entity.h"
#include "Character.h"

class Bullet :
	public Entity
{
public:
	Bullet();
	virtual ~Bullet();

	void update(std::shared_ptr<EntityData> entitydata);

private:

	void rotate(sf::Vector2f vec_dir);
	void setDir(std::shared_ptr<Character> owner, sf::Vector2f target);

	void initSprite();
	void initHitBox();

	void collisionWalls(std::vector<sf::FloatRect> walls);
	void collisionEnemies(const std::vector<std::shared_ptr<Character>> enemies);

	sf::Vector2f player_pos;
	sf::Vector2f dir;

	sf::Vector2f offset;
};


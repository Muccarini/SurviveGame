#pragma once
#include "Character.h"

class Bullet :
	public Entity
{
public:
	Bullet(BulletOwner::Owner owner, sf::Texture texture);
	Bullet();
	virtual ~Bullet();

	void update(std::shared_ptr<EntityData> entitydata);

	void setDir(sf::Vector2f owner_pos, sf::Vector2f target);

private:

	void rotate(sf::Vector2f vec_dir);

	void collisionWalls(std::vector<sf::FloatRect> walls);
	void collisionPlayer(std::shared_ptr<Character> player);
	void collisionEnemies(std::vector<std::shared_ptr<Character>> enemies);

	void initSprite();
	void initHitBox();

	sf::Vector2f owner_pos;
	sf::Vector2f dir;

	BulletOwner::Owner owner;


};


#pragma once
#include "Entity.h"

class Bullet :
	public Entity
{
public:
	Bullet();
	virtual ~Bullet();

	void update(std::shared_ptr<EntityData> entitydata);
	bool setDir(sf::Vector2f owner, sf::Vector2f target);

	void initSprite();
	void initHitBox();

private:

	void rotate(sf::Vector2f vec_dir);

	sf::Vector2f player_pos;
	sf::Texture texture;
	sf::Vector2f dir;

	sf::Vector2f offset;

	float ratio;
};


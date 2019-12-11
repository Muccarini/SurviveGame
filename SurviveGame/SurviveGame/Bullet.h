#pragma once
#include "Character.h"

class Bullet :
	public Entity
{
public:
	Bullet(const std::shared_ptr<Character> owner, sf::Texture texture);
	Bullet();
	virtual ~Bullet();

	void update(std::shared_ptr<EntityData> entitydata);

	void setDir(const sf::Vector2f owner_pos, const sf::Vector2f target);

private:

	void updateCollsion(std::shared_ptr<EntityData> entitydata);
	void rotate(sf::Vector2f vec_dir);
	void initSprite();
	void initHitBox();

	sf::Vector2f dir;
	std::shared_ptr<Character> owner;
};


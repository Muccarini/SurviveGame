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

	void setDir(const sf::Vector2f owner_pos, const sf::Vector2f target);

private:
	void updateMove(std::shared_ptr<EntityData> entitydata);

	void updateAlliedCollision(std::shared_ptr<EntityData> entitydata);
	void updateEnemyCollision(std::shared_ptr<EntityData> entitydata);
	void updateWallsCollision(std::shared_ptr<EntityData> entitydata);

	void updateRotate(sf::Vector2f vec_dir);

	void initSprite();
	void initHitBox();

	sf::Vector2f owner_pos;
	sf::Vector2f dir;

	BulletOwner::Owner owner;


};


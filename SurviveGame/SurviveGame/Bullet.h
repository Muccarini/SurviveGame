#pragma once
#include "Character.h"

class Bullet :
	public Entity
{
public:
	Bullet(BulletOwner::Owner owner, std::shared_ptr<EntityData> entitydata);
	Bullet();
	virtual ~Bullet();

	void update();

	void setDir();

private:
	void updateMove();

	void updateAlliedCollision();
	void updateEnemyCollision();
	void updateWallsCollision();

	void updateRotate(sf::Vector2f vec_dir);
	
	void initSpritePlayer();
	void initSpritePet();
	void initSpriteBoss();
	void initHitBox();

	sf::Vector2f dir;

	BulletOwner::Owner owner;


};


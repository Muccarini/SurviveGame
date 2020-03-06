#pragma once
#include "Character.h"

class Bullet :
	public Entity
{
public:
	Bullet(BulletOwner::Owner owner, sf::Vector2f owner_pos, sf::Texture texture);
	Bullet();
	virtual ~Bullet();

	void update(sf::Time deltaTime);

	void calculateDir(sf::Vector2f owner_pos, sf::Vector2f target);
	void setDir(sf::Vector2f dir);

private:
	void updateMove(sf::Time deltaTime);

	void updateAlliedCollision();
	void updateEnemyCollision();
	void updateWallsCollision();

	void updateRotate(sf::Vector2f vec_dir);
	
	void initSpritePlayer(sf::Vector2f owner_pos, sf::Texture texture);
	void initSpritePet(sf::Vector2f owner_pos, sf::Texture texture);
	void initSpriteBoss(sf::Vector2f owner_pos, sf::Texture texture);
	void initHitBox();

	sf::Vector2f dir;

	BulletOwner::Owner owner;
};


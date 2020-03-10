#pragma once
#include "Character.h"
#include "Enemy.h"
#include "Boss.h"
#include "PlayerT.h"
#include "Pet.h"

class Bullet :
	public Entity
{
public:
	Bullet(BulletOwner::Owner owner, sf::Vector2f owner_pos, sf::Texture texture);
	Bullet();
	virtual ~Bullet();

	void updateMove(sf::Time deltaTime);
	void updateRotate();

	void updateAlliedCollision(std::vector<std::shared_ptr<Enemy>> enemies, std::shared_ptr<Boss> boss, std::vector<sf::FloatRect> walls);
	void updateEnemyCollision(std::shared_ptr<PlayerT> player, std::shared_ptr<Pet> pet, std::vector<sf::FloatRect> walls);
	
	void calculateDir(sf::Vector2f owner_pos, sf::Vector2f target);
	void setDir(sf::Vector2f dir);

	BulletOwner::Owner getOwner();

private:

	void updateWallsCollision(std::vector<sf::FloatRect> walls);

	void initSpritePlayer(sf::Vector2f owner_pos, sf::Texture texture);
	void initSpritePet(sf::Vector2f owner_pos, sf::Texture texture);
	void initSpriteBoss(sf::Vector2f owner_pos, sf::Texture texture);
	void initHitBox();

	sf::Vector2f dir;

	BulletOwner::Owner owner;
};


#pragma once
#include "Character.h"
#include "Astar.h"
class Boss :
	public Character
{
public:
	explicit Boss(const std::shared_ptr<EntityData> entitydata);
	Boss();
	virtual ~Boss();

private:
	virtual void update();
	virtual void renderBullets(std::shared_ptr<sf::RenderWindow> target);

	void updateMove();
	void updateBullets();
	void updateRotate();
	void updateReload();
	void updateHud();
	void updateCollision();

	void updateShooting();

	bool isInRange(sf::Vector2f obj1, sf::Vector2f obj2);
	void takeDamage();

	void initVar();
	void initSprite();
	void initHitBox();

	std::vector<std::shared_ptr<Bullet>> bullets;
	sf::Texture texture_bullet;

	//movimento
	float distance;
	float max_distance;
	std::list <sf::Vector2f> move_vect;
	sf::Vector2f target;
	sf::Vector2f spostamento;

	AStar _m;
};


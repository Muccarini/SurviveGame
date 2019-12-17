#pragma once
#include "Character.h"

class Pet :
	public Character
{
public:
	explicit Pet(const std::shared_ptr<EntityData> entitydata);
	Pet();
	virtual ~Pet();

	void update();
	void renderBullets(std::shared_ptr<sf::RenderWindow> window);

private:

	void takeDamage();

	void updateMove();
	void updateRotate();
	void updateBullets();
	void updateHud();
	void updateCollision();

	void initVar();
	void initSprite();
	void initHitbox();

	std::vector<std::shared_ptr<Bullet>> bullets;
};


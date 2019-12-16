#pragma once
#include "Character.h"

class Boss :
	public Character
{
public:
	explicit Boss(std::shared_ptr<TextureHolder> textures);
	Boss();
	virtual ~Boss();

private:
	virtual void update(std::shared_ptr<EntityData> entitydata);
	virtual void renderBullets(std::shared_ptr<sf::RenderWindow> target);

	void updateMove(sf::Time deltaTime, std::shared_ptr<Character> target);
	void updateBullets(std::shared_ptr<EntityData> entitydata);
	void updateRotate(std::shared_ptr<Character> target);
	void updateReload(sf::Time deltaTime);
	void updateHud();
	void updateCollision(std::shared_ptr<EntityData> entitydata);

	void updateShooting(std::shared_ptr<EntityData> entitydata);

	bool isInRange(sf::Vector2f obj1, sf::Vector2f obj2);
	void takeDamage();

	void initVar();
	void initSprite();
	void initHitBox();

	std::vector<std::shared_ptr<Bullet>> bullets;
	sf::Texture texture_bullet;
};


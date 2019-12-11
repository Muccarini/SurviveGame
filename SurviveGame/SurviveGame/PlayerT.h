#pragma once
#include "Character.h"

class PlayerT :
	public Character
{
public:
	PlayerT(sf::Texture texture_player, sf::Texture texture_bullet);

	PlayerT();
	virtual ~PlayerT();

private:
	virtual void update(std::shared_ptr<EntityData> entitydata);
	virtual void renderBullets(std::shared_ptr<sf::RenderWindow> target);

	void updateMove(sf::Time deltaTime);
	void updateBullets(std::shared_ptr<EntityData> entitydata);
	void updateRotate(sf::Vector2f mousePosView);
	void updateReload(sf::Time deltaTime);
	void updateDash(sf::Vector2f dir, sf::Time deltaTime);
	void updateHud();
	void updateCollision(std::shared_ptr<EntityData> entitydata);

	bool isShooting(sf::Time deltaTime);

	void initVar();
	void initSprite();
	void initHitBox();

	std::vector<std::shared_ptr<Bullet>> bullets;

	void takeDamage();

	float dash_speed;
	float dash_cd;

	bool is_dashing;
};


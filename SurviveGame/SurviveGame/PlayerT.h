#pragma once
#include "Character.h"

class PlayerT :
	public Character
{
public:
	PlayerT(sf::Texture texture_player, sf::Texture texture_bullet, sf::Texture texture_player_movspeed);

	PlayerT();
	virtual ~PlayerT();

	virtual void update(std::shared_ptr<EntityData> entitydata);
	virtual void renderBullets(std::shared_ptr<sf::RenderWindow> target);

	void updateMove(sf::Time deltaTime);
	void updateBullets(std::shared_ptr<EntityData> entitydata);
	void updateRotate(sf::Vector2f mousePosView);
	void updateReload(sf::Time deltaTime);
	void updateDash(sf::Vector2f dir, sf::Time deltaTime);
	void updateMovSpeed(sf::Time deltaTime);
	void updateHud();
	void updateCollision(std::shared_ptr<EntityData> entitydata);

	bool isShooting(sf::Time deltaTime);


	void initVar();
	void initSprite();
	void initHitBox();

	std::vector<std::shared_ptr<Bullet>> bullets;

	virtual void takeDamage();

	sf::Texture texture_movspeed;
	sf::Texture texture_bullet;

	float dash_speed;
	float dash_cd;
	float dash_clock;

	float ms_cd;
	float ms_clock;

	bool is_dashing;
};


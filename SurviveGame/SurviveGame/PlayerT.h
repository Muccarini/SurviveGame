#pragma once
#include "Character.h"
#include "StrategyFight.h"

class PlayerT : public Character
{
public:
	explicit PlayerT(Textures::ID id, StrategyFight* stf);

	PlayerT();
	virtual ~PlayerT();

	virtual void renderBullets(std::shared_ptr<sf::RenderWindow> target);

	void updateMove(sf::Time deltaTime);
	void updateBullets(sf::Time deltaTime, sf::Vector2f target);
	void updateRotate();
	bool updateReload();
	void updateDash(sf::Vector2f dir);
	void updateMovSpeed(sf::Time deltaTime);
	void updateHud();
	void updateCollision();
	void updateDataPlayer();

	void updateShooting(sf::Time deltaTime);
	void setStrategyFight(StrategyFight* stf);

	void initVar();
	void initSprite();
	void initHitBox();

	std::vector<std::shared_ptr<Bullet>> bullets;

	virtual void takeDamage();

	Textures::ID getId();
	void setTexturesSprite(std::shared_ptr<TextureHolder> textures);

	sf::Texture texture_movspeed;
	sf::Texture texture_bullet;

	float dash_speed;
	float dash_cd;
	float dash_clock;

	float ms_cd;
	float ms_clock;

	bool is_dashing;
private:

	Textures::ID id;
	StrategyFight* stf;
	void setType();

	int kills;
	int kills_boss;

};


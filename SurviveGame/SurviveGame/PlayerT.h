#pragma once
#include "Character.h"

class PlayerT :
	public Character
{
public:
	PlayerT();
	virtual ~PlayerT();

	void update(std::shared_ptr<EntityData> entitydata);

private:

	void updateMove(sf::Time deltaTime);
	void updateRotate(sf::Vector2f mousePosView);
	void updateReload(sf::Time deltaTime);
	void updateDash(sf::Vector2f dir, sf::Time deltaTime);
	void updateHud();

	void initVar();
	void initSprite();
	void initHitBox();

	float dash_speed;
	float dash_cd;

	bool is_dashing;
};

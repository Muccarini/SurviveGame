#pragma once
#include "Character.h"

class Pet :
	public Character
{
public:
	Pet(const sf::Texture & texture, const sf::Vector2f spawn_pos);
	Pet();
	virtual ~Pet();

	void updateMove(const sf::Time& delta_time, const sf::Vector2f parent_pos);
	void updateRotate(const sf::Vector2f target);
	void updateHud();

private:
	void initVar();
	void initSprite(const sf::Texture & texture, const sf::Vector2f spawn_pos);
	void initHitbox();
};


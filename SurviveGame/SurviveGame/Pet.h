#pragma once
#include "Character.h"

class Pet :
	public Character
{
public:
	explicit Pet(const sf::Texture & texture, sf::Vector2f spawn_pos);
	Pet();
	virtual ~Pet();

	void updateMove(sf::Time deltaTime, sf::Vector2f parent_pos);
	void updateRotate(sf::Vector2f target);
	void updateHud();
	void updateCollision(sf::FloatRect parent_rect);

	void takeDamage();

private:

	void initVar();
	void initSprite(const sf::Texture & texture, sf::Vector2f spawn_pos);
	void initHitbox();
};


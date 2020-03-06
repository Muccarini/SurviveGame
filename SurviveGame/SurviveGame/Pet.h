#pragma once
#include "Character.h"

class Pet :
	public Character
{
public:
	explicit Pet(sf::Texture texture, sf::Vector2f spawn_pos);
	Pet();
	virtual ~Pet();

	void updateMove(sf::Time deltaTime, sf::Vector2f parent_pos);
	void updateRotate(sf::Vector2f target);
	void updateBullets(bool player_shooting, int player_ammo, sf::Vector2f bullet_pos, sf::Texture bullet_txt, sf::Vector2f target);
	void updateHud();
	void updateCollision(sf::FloatRect parent_rect);

	void renderBullets(std::shared_ptr<sf::RenderWindow> window);

private:
	void takeDamage();

	void initVar();
	void initSprite(sf::Texture texture, sf::Vector2f spawn_pos);
	void initHitbox();

	std::vector<std::shared_ptr<Bullet>> bullets;
};


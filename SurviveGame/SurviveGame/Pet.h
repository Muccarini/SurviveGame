#pragma once
#include "Character.h"

class Pet :
	public Character
{
public:
	Pet(sf::Texture txt_p, sf::Texture txt_b, sf::Vector2f spawn_pos);
	virtual ~Pet();

	void update(std::shared_ptr<EntityData> entitydata);
	void renderBullets(std::shared_ptr<sf::RenderWindow> window);

private:

	void takeDamage();

	void updateMove(std::shared_ptr<Character> target, sf::Time deltaTime);
	void updateBullets(std::shared_ptr<EntityData> entitydata);
	void updateHud();

	void initVar();
	void initSprite(sf::Vector2f spawn_pos);
	void initHitbox();

	std::vector<std::shared_ptr<Bullet>> bullets;

	sf::Texture texture_bullet;
};


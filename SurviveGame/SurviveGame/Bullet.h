#pragma once
#include "GameCharacter.h"
#include "Enemy.h"
class Bullet :
	public GameCharacter
{
public:
	Bullet(sf::Vector2f player_pos);
	Bullet();
	~Bullet();

	void update(sf::Time deltaTime, sf::Vector2f mousePosView, std::vector<sf::FloatRect> collision, std::vector<std::shared_ptr<Enemy>> enemies);

private:

	void rotate(sf::Vector2f vec_dir);

	sf::Vector2f player_pos;
	float ratio;
};


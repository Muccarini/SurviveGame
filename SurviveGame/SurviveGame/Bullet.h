#pragma once
#include "GameCharacter.h"
#include "Enemy.h"
class Bullet :
	public GameCharacter
{
public:
	Bullet();
	~Bullet();

	void update(sf::Time deltaTime, sf::Vector2f mousePosView, std::vector<sf::FloatRect> collision, std::vector<std::shared_ptr<Enemy>> enemies);
	void init(sf::Vector2f player_pos);

private:

	void rotate(sf::Vector2f vec_dir);

	sf::Vector2f player_pos;
	float ratio;
};


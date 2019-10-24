#pragma once
#include "GameCharacter.h"
#include "Enemy.h"
#include "Player.h"

class Bullet :
	public GameCharacter
{
public:
	Bullet();
	virtual ~Bullet();
	// Player* DA GENERALIZZARE CON GAMECHARACTER
	bool update(sf::Time deltaTime, std::vector<sf::FloatRect> collision, std::vector<std::shared_ptr<Enemy>> enemies);
	bool init(sf::Vector2f owner, sf::Vector2f mousePosView, int ammo);

private:

	void rotate(sf::Vector2f vec_dir);

	sf::Vector2f player_pos;

	sf::Vector2f dir;
	int number;
	
	float ratio;
};


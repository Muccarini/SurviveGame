#pragma once
#include "GameCharacter.h"
#include "Enemy.h"
#include "Player.h"

class Bullet :
	public GameCharacter
{
public:
	Bullet(sf::Texture txt);
	Bullet();
	virtual ~Bullet();
	// Player* DA GENERALIZZARE CON GAMECHARACTER
	bool update(sf::Time deltaTime, std::vector<sf::FloatRect> collision, std::vector<std::shared_ptr<Enemy>> enemies);
	bool setDir(sf::Vector2f owner, sf::Vector2f target);

private:

	void rotate(sf::Vector2f vec_dir);

	sf::Vector2f player_pos;
	sf::Texture texture;
	sf::Vector2f dir;

	sf::Vector2f offset;

	float ratio;
};


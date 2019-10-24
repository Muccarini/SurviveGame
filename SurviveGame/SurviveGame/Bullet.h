#pragma once
#include "GameCharacter.h"
#include "Enemy.h"
#include "Player.h"

class Bullet :
	public GameCharacter
{
public:
	Bullet();
	~Bullet();
	// Player* DA GENERALIZZARE CON GAMECHARACTER
	void update(sf::Time deltaTime, std::vector<sf::FloatRect> collision, std::vector<std::shared_ptr<Enemy>> enemies);
	bool init(Player *player, sf::Vector2f mousePosView);

private:

	void rotate(sf::Vector2f vec_dir);

	sf::Vector2f player_pos;

	sf::Vector2f dir;
	
	float ratio;
};


#pragma once
#include "GameCharacter.h"
#include "Enemy.h"

class Player :
	public GameCharacter
{
public:
	enum Type {Warrior, Ranger, Mage};
	
public:
	Player();
	virtual ~Player();

	void update(sf::Time deltaTime, sf::Vector2f mousePosView, std::vector<sf::FloatRect> collision, std::vector<std::shared_ptr<Enemy>> enemies);
	
	void move(sf::Time deltaTime);
	void rotate(sf::Vector2f mousePosView);
	void reload(sf::Time deltaTime);

	bool isShooting(sf::Time deltaTime);

private:

	Type _type;
	sf::Texture texture;

	sf::Time reload_time;
	sf::Time ratio;

};


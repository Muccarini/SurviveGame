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
	bool isShooting(sf::Time deltaTime);

private:
	void initSprite();
	void initHitBox();

	void move(sf::Time deltaTime);
	void rotate(sf::Vector2f mousePosView);
	void reload(sf::Time deltaTime);

	Type _type;
	sf::Texture texture;

	sf::Time reload_time;
	sf::Time ratio;

};


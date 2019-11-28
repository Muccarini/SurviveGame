#pragma once
#include "GameCharacter.h"

class Boss :
	public GameCharacter
{
public:
	Boss();
	virtual ~Boss();

	void update(sf::Time deltaTime, GameCharacter* target, std::vector<sf::FloatRect> collision);
	bool isShooting(sf::Time deltaTime);

private:
	void initSprite();
	void initHitBox();

	void reload(sf::Time deltaTime);

	sf::Texture texture;

	sf::Time reload_cd;
	sf::Time reload_clock;
	sf::Time ratio;
};


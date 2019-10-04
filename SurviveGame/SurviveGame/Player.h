#pragma once
#include "GameCharacter.h"

class Player :
	public GameCharacter
{
public:
	enum Type {Warrior, Ranger, Mage};
	
public:
	explicit Player();
	virtual ~Player();
	
	void move(sf::Time deltaTime);
	void rotate(sf::RenderWindow *_window);

	void update(sf::Time deltaTime, sf::RenderWindow * _window);

	sf::Vector2f getPosition();

	sf::View view;


private:
	Type _type;
};


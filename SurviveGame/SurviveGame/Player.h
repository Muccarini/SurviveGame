#pragma once
#include "GameCharacter.h"
#include "PlayerStrategyMove.h"
#include <list>

class Player :
	public GameCharacter
{
public:
	enum Type {Warrior, Ranger, Mage};
	
public:
	explicit Player();
	virtual ~Player();
	
	 void move(sf::Time deltaTime);

	 void update(sf::RenderWindow &target, sf::Time deltaTime, sf::Vector2f mousePosView);
	 virtual void notify(sf::RenderWindow &target) override;

	 virtual void subscribe(Observer* _O);
	 virtual void unsubscribe(Observer* _O);


	void setPositon(sf::Vector2f vMove);
	sf::Vector2f getPosition();

private:

	Type _type;
	PlayerStrategyMove _m;
	std::list<Observer *> _observers;
};


#pragma once
#include "GameCharacter.h"
#include "EnemyStrategyMove.h"
#include "Player.h"

class Enemy :
	public GameCharacter
{
public:
	enum Type {Ranged, Melee, Boss};

public:
	Enemy();
	virtual ~Enemy();

	 void move(sf::Time deltaTime);

	 void update(sf::RenderWindow &screen, sf::Time deltaTime, Player* target);

	 virtual void notify(sf::RenderWindow &target) override;

	 virtual void subscribe(Observer* _O);
	 virtual void unsubscribe(Observer* _O);
	 
	 sf::Vector2f getPosition();

private:
	EnemyStrategyMove _m;
	std::list<Observer *> _observers;
};


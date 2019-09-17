#pragma once
#include "Observer.h"
class Subject
{
public:
	virtual ~Subject() {};

	virtual void subscribe(Observer* _O)   = 0;
	virtual void unsubscribe(Observer* _O) = 0;
	
	virtual void notify(sf::RenderWindow &target) = 0;
};
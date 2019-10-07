#pragma once
class Observer
{
public:
	virtual ~Observer() {};

	virtual void update(sf::RenderWindow& target) = 0;

	virtual void attach() = 0;
	virtual void detach() = 0;


};


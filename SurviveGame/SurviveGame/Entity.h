#pragma once
#include<SFML/Graphics.hpp>

class Entity
{
public:
	Entity();

	virtual void move() = 0;

	virtual void update()=0;
	virtual void render()=0;
};


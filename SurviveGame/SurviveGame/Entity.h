#pragma once
#include "StrategyMove.h"
#include"TextureHolder.h"

class Entity
{
public:
	Entity();
	virtual ~Entity();

	virtual void update()=0;
	virtual void render()=0
};


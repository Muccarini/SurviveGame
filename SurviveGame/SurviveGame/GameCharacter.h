#pragma once
#include "Entity.h"
class GameCharacter :
	public Entity
{
public:
	enum Type {Eagle, Raptor};
public:
	explicit GameCharacter(Type type);

private:
	Type _type;
};


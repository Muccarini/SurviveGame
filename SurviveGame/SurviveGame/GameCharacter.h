#pragma once
#include "Entity.h"
class GameCharacter :
	public Entity
{
public:
	enum Type {Warrior, Ranger, Mage};
public:
	explicit GameCharacter(Type type);

private:
	Type _type;
};


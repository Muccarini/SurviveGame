#pragma once
#include "Entity.h"
#include "TextureHolder.h"
#include "StrategyMove.h"
#include "SFML/Graphics.hpp"
class GameCharacter :
	public Entity , public sf::Sprite
{
public:
	enum Type {Warrior, Ranger, Mage};
	
public:
	explicit GameCharacter(Type type);
	void move();

private:
	Type _type;
	TextureHolder _textures;  //CON TextureHolder POSSIAMO GESTIRE PIU TEXTURE ALLA VOLTA (LOAD AND GET)
	sf::Sprite _sprite;   // SPRITE NE GESTICE LA POSIZIONE E L'ORIENTAMENTO
	StrategyMove _move;
};


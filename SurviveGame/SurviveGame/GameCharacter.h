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
	explicit GameCharacter();
	sf::Vector2f & move();

	bool isMoving = false;
	sf::Sprite _sprite; // SPRITE NE GESTICE LA POSIZIONE E L'ORIENTAMENTO

private:
	Type _type;
	TextureHolder _textures;  //CON TextureHolder POSSIAMO GESTIRE PIU TEXTURE ALLA VOLTA (LOAD AND GET)
	StrategyMove _move;
};


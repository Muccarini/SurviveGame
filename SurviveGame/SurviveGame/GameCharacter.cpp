#include "GameCharacter.h"

GameCharacter::GameCharacter(Type type, StrategyMove _m) : _type(type)
{
	_textures.load(Textures::Personaggio, "$(SolutionDir)/Sprite_laila_run2.png");
	_player.setTexture(_textures.get(Textures::Personaggio));
	this->_move = _m;
}

void GameCharacter::Move()
{
	this->_move.MoveS(&(_player.getPosition()), _player);
}

#include "GameCharacter.h"

GameCharacter::GameCharacter() : _type()
{
	_textures.load(Textures::Personaggio, "$(SolutionDir)/Sprite_laila_run2.png");
	_sprite.setTexture(_textures.get(Textures::Personaggio));
	_sprite.setPosition(100.f, 100.f);
}

sf::Vector2f GameCharacter::move()
{
	return this->_move.MoveS(&(_sprite.getPosition()), _sprite);
}

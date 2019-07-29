#include "GameCharacter.h"

GameCharacter::GameCharacter()
{
	//_textures.load(Textures::Personaggio, "Sources/Sprite_laila_run2.png");
	//_sprite.setTexture(_textures.get(Textures::Personaggio));
	//_sprite.setPosition(100.f, 100.f);
	//_sprite.setTextureRect(sf::IntRect(0, 0, 32, 48));
}

sf::Vector2f& GameCharacter::move()
{
	return 
		this->_move.MoveS(_sprite.getPosition(), _sprite);
}

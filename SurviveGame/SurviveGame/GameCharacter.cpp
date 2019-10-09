#include "GameCharacter.h"



GameCharacter::GameCharacter()
{
}


GameCharacter::~GameCharacter()
{
}

void GameCharacter::render(sf::RenderWindow * target)
{
	target->draw(_sprite);
}

sf::Vector2f GameCharacter::getPosition()
{
	return
		this->_sprite.getPosition();
}

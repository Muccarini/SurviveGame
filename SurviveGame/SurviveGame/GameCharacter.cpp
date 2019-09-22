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
	target->draw(_sprShape);
}

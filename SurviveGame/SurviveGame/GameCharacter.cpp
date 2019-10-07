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

void GameCharacter::update(sf::Time deltaTime, sf::Vector2f mousePosView)
{
	move(deltaTime);
	rotate(mousePosView);
}

void GameCharacter::update(sf::Time deltaTime, GameCharacter * target)
{
	float dX = target->getPosition().x - this->_sprite.getPosition().x;
	float dY = target->getPosition().y - this->_sprite.getPosition().y;

	float lenght = sqrt(pow(dX, 2) + pow(dY, 2));

	sf::Vector2f normVect(dX / lenght, dY / lenght);
	this->_sprite.move(normVect * this->mov_speed * deltaTime.asSeconds()); 

	rotate(normVect);
}

sf::Vector2f GameCharacter::getPosition()
{
	return
		this->_sprite.getPosition();
}

#include "Enemy.h"
#include <math.h>



Enemy::Enemy()
{
	_movementSpeed = 0.8;

	_textures.load(Textures::Enemy, "Sources/Sprite_laila_run2.png");
	_sprite.setTexture(_textures.get(Textures::Enemy));
	_sprite.setPosition(200.f, 200.f);
	//_sprite.setTextureRect(sf::IntRect(0, 0, 32, 48));
}


Enemy::~Enemy()
{
}

void Enemy::move(sf::Time deltaTime)
{
	this->_m.move(deltaTime, this->_sprite, this->_movementSpeed);
}

void Enemy::update(sf::Time deltaTime, Player* target)
{
	sf::Vector2f targetPos = target->getPosition();
	sf::Vector2f enemyPos = this->_sprite.getPosition();

	sf::Vector2f movementVector = (targetPos - enemyPos);

	this->_sprite.move(movementVector * deltaTime.asSeconds()* this->_movementSpeed);

	          // D //
	if (movementVector.x > 0)
		if ((fabs(movementVector.y) / movementVector.x) < 1)
			_sprite.setTextureRect(sf::IntRect(0 * 32, 48 * 3, 32, 48));;

		
	          // A //
	if (movementVector.x < 0)
		if((fabs(movementVector.y) / fabs(movementVector.x)) < 1 )
			_sprite.setTextureRect(sf::IntRect(0 * 32, 48 * 2, 32, 48));
		
	          // S //
	if(movementVector.y > 0)
		_sprite.setTextureRect(sf::IntRect(0 * 32, 0, 32, 48));

	          // W //
	if(movementVector.y < 0)
		_sprite.setTextureRect(sf::IntRect(0 * 32, 48, 32, 48));

	


     //TODO//
	// il personaggio verra' cambiato frame provvisori
	//il movimento e' fluido perche' il vettore varia sempre
	//avendo mS a moltiplicare non abbiamo un movimento costante 
}

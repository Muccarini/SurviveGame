#include "Enemy.h"
#include <math.h>


Enemy::Enemy()
{
	mov_speed = 100;

	_textures.load(Textures::Enemy, "Sources/zombie1.png");
	_sprite.setTexture(_textures.get(Textures::Enemy));
	_sprite.setScale(0.3f, 0.3f);
	_sprite.setPosition(200.f, 200.f);
	_sprite.setOrigin(+34, +34);
	_sprite.setTextureRect(sf::IntRect(0, 0, 68, 68));
}


Enemy::~Enemy()
{
}

void Enemy::move(sf::Time deltaTime)
{
	this->_m.move(deltaTime, this->_sprite, this->mov_speed);
}

void Enemy::rotate(sf::Vector2f vec_dir)
{
	const float PI = 3.14159265f;
	float deg = atan2(vec_dir.y, vec_dir.x ) * 180.f / PI;

	this->_sprite.setRotation(deg + 90.f);
}


//void Enemy::update(sf::Time deltaTime, GameCharacter* target)
//{   
//	            //MOVEMENT//
//	float dX = target->getPosition().x - this->_sprite.getPosition().x;
//	float dY = target->getPosition().y - this->_sprite.getPosition().y;
//
//	float lenght = sqrt(pow(dX, 2) + pow(dY, 2));
//
//	sf::Vector2f normVect(dX / lenght, dY / lenght);
//
//	this->_sprite.move(normVect * this->mov_speed * deltaTime.asSeconds());
//
//	rotate(normVect);
//}

//sf::Vector2f Enemy::getPosition()
//{
//	return
//		this->_sprite.getPosition();
//}


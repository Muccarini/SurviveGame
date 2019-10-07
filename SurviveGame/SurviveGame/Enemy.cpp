#include "Enemy.h"
#include <math.h>


Enemy::Enemy(float x, float y) : spawn_pos(x,y)
{
	mov_speed = 100;

	_textures.load(Textures::Enemy, "Sources/zombie1.png");
	_sprite.setTexture(_textures.get(Textures::Enemy));
	_sprite.setScale(0.3f, 0.3f);
	_sprite.setPosition(spawn_pos);
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

#include "Enemy.h"
#include <math.h>


Enemy::Enemy(float x, float y) : spawn_pos(x,y)
{
	mov_speed = 100;

	_textures.load(Textures::Enemy, "Sources/zombie1.png");
	_sprite.setTexture(_textures.get(Textures::Enemy));
	hit_box.setSize(sf::Vector2f(50.f, 50.f));

	//COLOR
	hit_box.setOutlineColor(sf::Color::Transparent);
	hit_box.setOutlineThickness(3.f);
	hit_box.setFillColor(sf::Color::Transparent);
	//SCALE
	_sprite.setScale(0.9f, 0.9f);
	hit_box.setScale(_sprite.getScale());
	//POSITION
	_sprite.setPosition(spawn_pos);
	hit_box.setPosition(getPosition());
	//ORIGIN
	_sprite.setOrigin(+34, +34);
	hit_box.setOrigin(20, 25);

	_sprite.setTextureRect(sf::IntRect(0, 0, 68, 68));
}


Enemy::~Enemy()
{
}

 void Enemy::move(sf::Time deltaTime)
{
	//this->_m.move(deltaTime, this->_sprite, this->mov_speed);
}


void Enemy::rotate(sf::Vector2f vec_dir)
{
	const float PI = 3.14159265f;
	float deg = atan2(vec_dir.y, vec_dir.x ) * 180.f / PI;

	this->_sprite.setRotation(deg + 90.f);
}

void Enemy::update(sf::Time deltaTime, GameCharacter * target, std::vector<sf::FloatRect> collision, std::vector<std::shared_ptr<Enemy>> enemies)
{
	float dX = target->getPosition().x - this->_sprite.getPosition().x;
	float dY = target->getPosition().y - this->_sprite.getPosition().y;

	float lenght = sqrt(pow(dX, 2) + pow(dY, 2));

	sf::Vector2f normVect(dX / lenght, dY / lenght);

	this->_sprite.move(normVect * this->mov_speed * deltaTime.asSeconds());
	hit_box.setPosition(getPosition());

	//COLLISON SUI MURI

	for (int i = 0; i != collision.size(); i++)
	{
		if (sat_test(hit_box.getGlobalBounds(), collision[i], &out_mtv))
		{
			_sprite.move(out_mtv);
		}
	}
	//COLLISION SUGLI ALTRI ZOMBIE

	for (int i = 0; i != enemies.size(); i++)
	{
		if(enemies[i]->hit_box.getGlobalBounds() != hit_box.getGlobalBounds())
			if (sat_test(hit_box.getGlobalBounds(), enemies[i]->hit_box.getGlobalBounds(), &out_mtv))
			{
				_sprite.move(out_mtv);
			}
	}

	rotate(normVect);
}


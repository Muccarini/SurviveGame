#include "Enemy.h"
#include <math.h>


Enemy::Enemy(float x, float y, sf::Texture txt) : spawn_pos(x,y), texture(txt)
{
	mov_speed = 100;
	hp = 10;

	initSprite();
	initHitBox();
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
	//MOVE DA CAMBIARE CI STIAMO LAVORANDO
	float dX = target->getPosition().x - this->_sprite.getPosition().x;
	float dY = target->getPosition().y - this->_sprite.getPosition().y;

	float lenght = sqrt(pow(dX, 2) + pow(dY, 2));

	sf::Vector2f normVect(dX / lenght, dY / lenght);

	this->_sprite.move(normVect * this->mov_speed * deltaTime.asSeconds());
	hit_box.setPosition(getPosition());
	
	gui.updateText(ammo, hp, getPosition());

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

void Enemy::initSprite()
{
	_sprite.setTexture(texture);
	_sprite.setScale(0.9f, 0.9f);
	_sprite.setPosition(spawn_pos);
	_sprite.setOrigin(+34, +34);
	_sprite.setTextureRect(sf::IntRect(0, 0, 68, 68));
}

void Enemy::initHitBox()
{
	hit_box.setSize(sf::Vector2f(50.f, 50.f));
	hit_box.setOutlineColor(sf::Color::Transparent);
	hit_box.setOutlineThickness(3.f);
	hit_box.setFillColor(sf::Color::Transparent);
	hit_box.setScale(_sprite.getScale());
	hit_box.setPosition(getPosition());
	hit_box.setOrigin(20, 25);
}


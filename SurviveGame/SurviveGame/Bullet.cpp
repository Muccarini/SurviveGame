#include "Bullet.h"



Bullet::Bullet()
{
	mov_speed = 1500;

	initSprite();
	initHitBox();
}

Bullet::~Bullet()
{
}

void Bullet::update(std::shared_ptr<EntityData> entitydata)
{
	this->sprite.move(this->dir.x * this->mov_speed * deltaTime.asSeconds(), this->dir.y * this->mov_speed * deltaTime.asSeconds());
	hit_box.setPosition(getPosition());

	//COLLISON SUI MURI

	for (int i = 0; i != collision.size(); i++)
	{
		if (sat_test(hit_box.getGlobalBounds(), collision[i], &out_mtv))
		{
			return false;
		}
	}
	//COLLISION SUGLI ALTRI ZOMBIE

	for (int i = 0; i != enemies.size(); i++)
	{
			if (sat_test(hit_box.getGlobalBounds(), enemies[i]->hit_box.getGlobalBounds(), &out_mtv))
			{
				enemies[i]->takeDamage();
				return false;
			}
	}

	float dX = getPosition().x - player_pos.x;
	float dY = getPosition().y - player_pos.y;
	float distance = sqrt(pow(dX, 2) + pow(dY, 2));

	if (distance > 1200)
		return false;

	rotate(dir);
}

bool Bullet::setDir(sf::Vector2f owner, sf::Vector2f mousePosView)
{
	this->player_pos = owner;

	sprite.setPosition(owner);
	float dX = mousePosView.x - owner.x;
	float dY = mousePosView.y - owner.y;

	float lenght = sqrt(pow(dX, 2) + pow(dY, 2));

	sf::Vector2f normVect(dX / lenght, dY / lenght);

	dir = normVect;

	return true;
}

void Bullet::initSprite()
{
	sprite.setTexture(textures.get(Textures::Proiettile));
	sprite.setScale(0.013, 0.013);
	sprite.setOrigin(-3500, -562);
}

void Bullet::initHitBox()
{
	hit_box.setSize(sf::Vector2f(813.f, 306.f));
	hit_box.setOutlineColor(sf::Color::Transparent);
	hit_box.setOutlineThickness(3.f);
	hit_box.setFillColor(sf::Color::Transparent);
	hit_box.setScale(sprite.getScale());
	hit_box.setOrigin(sprite.getOrigin());
}


void Bullet::rotate(sf::Vector2f vec_dir)
{
	const float PI = 3.14159265f;
	float deg = atan2(vec_dir.y, vec_dir.x) * 180.f / PI;

	this->sprite.setRotation(deg);
	this->hit_box.setRotation(deg);
}
#include "Bullet.h"



Bullet::Bullet(BulletOwner::Owner owner, sf::Texture txt)
{
	this->owner = owner;
	this->texture = txt;

	this->mov_speed = 1500;

	initSprite();
	initHitBox();
}

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::update(std::shared_ptr<EntityData> entitydata)
{
	this->sprite.move(this->dir.x * this->mov_speed * entitydata->deltaTime.asSeconds(), this->dir.y * this->mov_speed * entitydata->deltaTime.asSeconds());
	hit_box.setPosition(sprite.getPosition());
	/*switch(this->owner)
	{
	case(BulletOwner::Allied):
		collisionEnemies(*entitydata->enemies);
		break;
	case(BulletOwner::Enemy):
		collisionPlayer(entitydata->player);
		break;
	}
	collisionWalls(entitydata->walls);*/

	updateCollision(entitydata);

	float dX = sprite.getPosition().x - owner_pos.x;
	float dY = sprite.getPosition().y - owner_pos.y;
	float distance = sqrt(pow(dX, 2) + pow(dY, 2));

	rotate(dir);
}

void Bullet::setDir(sf::Vector2f owner_pos, sf::Vector2f target)
{
	this->owner_pos = owner_pos;

	this->sprite.setPosition(owner_pos);
	float dX = target.x - owner->getPosition().x;
	float dY = target.y - owner->getPosition().y;

	float lenght = sqrt(pow(dX, 2) + pow(dY, 2));

	sf::Vector2f normVect(dX / lenght, dY / lenght);

	this->dir = normVect;
}

void Bullet::initSprite()
{
	sprite.setTexture(texture);
	sprite.setScale(0.013f, 0.013f);
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

void Bullet::updateCollision(std::shared_ptr<EntityData> entitydata)
{
	//PLAYER CASE
	if (this->owner == entitydata->player)
	{
		std::vector<std::shared_ptr<Character>> enemies;
		enemies = *entitydata->enemies;

		for (int i = 0; i != enemies.size(); i++)
		{
			collision->CollideWithEntity(this->hit_box.getGlobalBounds(), enemies[i]->getHitBox().getGlobalBounds());
			if (collision->isCollide())
			{
				enemies[i]->takeDamage();
				collision->resetOutMtv();
				continue;
			}
		}
		if (!collision->isCollide())
		{
			collision->CollideWithEntity(this->hit_box.getGlobalBounds(), entitydata->boss->getHitBox().getGlobalBounds());
			if (collision->isCollide())
			{
				entitydata->boss->takeDamage();
				collision->resetOutMtv();
			}
			else //WALL CASE
			{
				collision->CollideWithWalls(this->hit_box.getGlobalBounds(), entitydata->map->findWalls(sprite.getPosition().x, sprite.getPosition().y));
				collision->resetOutMtv();
			}
		}
	}
	//BOSS CASE
	else if (this->owner == entitydata->boss)
	{
		collision->CollideWithEntity(this->hit_box.getGlobalBounds(), entitydata->player->getHitBox().getGlobalBounds());
		if (collision->isCollide())
		{
			entitydata->player->takeDamage();
			collision->resetOutMtv();
		}
		else //WALL CASE
		{
			collision->CollideWithWalls(this->hit_box.getGlobalBounds(), entitydata->map->findWalls(sprite.getPosition().x, sprite.getPosition().y	));
			collision->resetOutMtv();
		}
	}

	this->collide = collision->isCollide();
}

void Bullet::rotate(sf::Vector2f vec_dir)
{
	const float PI = 3.14159265f;
	float deg = atan2(vec_dir.y, vec_dir.x) * 180.f / PI;

	this->sprite.setRotation(deg);
	this->hit_box.setRotation(deg);
}
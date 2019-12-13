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
	updateMove(entitydata);

	switch(this->owner)
	{
	case(BulletOwner::Allied):
		updateAlliedCollision(entitydata);
		break;
	case(BulletOwner::Enemy):
		updateEnemyCollision(entitydata);
		break;
	}

	/*float dX = sprite.getPosition().x - owner_pos.x;
	float dY = sprite.getPosition().y - owner_pos.y;
	float distance = sqrt(pow(dX, 2) + pow(dY, 2));*/

	updateRotate(dir);
}

void Bullet::setDir(sf::Vector2f owner_pos, sf::Vector2f target)
{
	this->owner_pos = owner_pos;

	this->sprite.setPosition(owner_pos);
	float dX = target.x - owner_pos.x;
	float dY = target.y - owner_pos.y;

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

void Bullet::updateMove(std::shared_ptr<EntityData> entitydata)
{
	this->sprite.move(this->dir.x * this->mov_speed * entitydata->deltaTime.asSeconds(), this->dir.y * this->mov_speed * entitydata->deltaTime.asSeconds());
	hit_box.setPosition(sprite.getPosition());
}

void Bullet::updateAlliedCollision(std::shared_ptr<EntityData> entitydata)
{
	//ALLIED CASE
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
		//WALLS
		else
			updateWallsCollision(entitydata);
	}

	this->collide = collision->isCollide();
}

void Bullet::updateEnemyCollision(std::shared_ptr<EntityData> entitydata)
{
	//BOSS
	collision->CollideWithEntity(this->hit_box.getGlobalBounds(), entitydata->player->getHitBox().getGlobalBounds());
	if (collision->isCollide())
	{
		entitydata->player->takeDamage();
		collision->resetOutMtv();
	}
	//WALLS
	else updateWallsCollision(entitydata);

	this->collide = collision->isCollide();
}

void Bullet::updateWallsCollision(std::shared_ptr<EntityData> entitydata)
{
	//WALLS
	collision->CollideWithWalls(this->hit_box.getGlobalBounds(), entitydata->map->findWalls(sprite.getPosition().x, sprite.getPosition().y));
	collision->resetOutMtv();
}

void Bullet::updateRotate(sf::Vector2f vec_dir)
{
	const float PI = 3.14159265f;
	float deg = atan2(vec_dir.y, vec_dir.x) * 180.f / PI;

	this->sprite.setRotation(deg);
	this->hit_box.setRotation(deg);
}
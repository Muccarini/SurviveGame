#include "Bullet.h"

Bullet::Bullet(BulletOwner::Owner owner, sf::Vector2f owner_pos, sf::Texture texture)
{
	this->owner = owner;

	this->mov_speed = 1500;

	switch(owner)
	{
	case(BulletOwner::Player):
		initSpritePlayer(owner_pos, texture);
		initHitBox();
		break;
	case(BulletOwner::Boss):
		initSpriteBoss(owner_pos, texture);
		initHitBox();
		break;
	case(BulletOwner::Pet):
		initSpritePet(owner_pos, texture);
		initHitBox();
		break;
	}
}

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::update(sf::Time deltaTime)
{
	updateMove(deltaTime);

	switch(this->owner)
	{
	case(BulletOwner::Player):
		updateAlliedCollision();
		break;

	case(BulletOwner::Pet):
		updateAlliedCollision();
		break;

	case(BulletOwner::Boss):
		updateEnemyCollision();
		break;
	}

	updateRotate(dir);
}

void Bullet::calculateDir(sf::Vector2f owner_pos, sf::Vector2f target)
{
	float dx;
	float dy;
	float lenght;
	sf::Vector2f normVect;
	switch (this->owner)
	{
	case(BulletOwner::Pet):
		dx = target.x - owner_pos.x;
		dy = target.y - owner_pos.y;
		sprite.setPosition(owner_pos);
		hit_box.setPosition(sprite.getPosition());
		break;
	case(BulletOwner::Boss):
		dx = target.x - owner_pos.x;
		dy = target.y - owner_pos.y;
		sprite.setPosition(owner_pos);
		hit_box.setPosition(sprite.getPosition());
		break;
	}
	lenght = sqrt(pow(dx, 2) + pow(dy, 2));
	normVect = sf::Vector2f(dx / lenght, dy / lenght);
	this->dir = normVect;
}

void Bullet::setDir(sf::Vector2f dir)
{
	this->dir = dir;
}

void Bullet::initSpritePet(sf::Vector2f owner_pos, sf::Texture texture)
{
	sprite.setTexture(texture);
	sprite.setPosition(owner_pos);
	sprite.setScale(0.013f, 0.013f);
	this->sprite.setOrigin(-500, 0);
}

void Bullet::initSpriteBoss(sf::Vector2f owner_pos, sf::Texture texture)
{
	sprite.setTexture(texture);
	sprite.setPosition(owner_pos);
	sprite.setScale(0.013f, 0.013f);
	this->sprite.setOrigin(-3500, -562);
}

void Bullet::initSpritePlayer(sf::Vector2f owner_pos, sf::Texture texture)
{
	sprite.setTexture(texture);
	sprite.setPosition(owner_pos);
	sprite.setScale(0.013f, 0.013f);
	this->sprite.setOrigin(-3500, -562);
}

void Bullet::initHitBox()
{
	hit_box.setSize(sf::Vector2f(813.f, 306.f));
	hit_box.setOutlineColor(sf::Color::Transparent);
	hit_box.setOutlineThickness(3.f);
	hit_box.setFillColor(sf::Color::Transparent);
	hit_box.setPosition(this->getPosition());
	hit_box.setScale(sprite.getScale());
	hit_box.setOrigin(sprite.getOrigin());
}

void Bullet::updateMove(sf::Time deltaTime)
{
	this->sprite.move(this->dir.x * this->mov_speed * deltaTime.asSeconds(), this->dir.y * this->mov_speed * deltaTime.asSeconds());
	hit_box.setPosition(sprite.getPosition());
}

void Bullet::updateAlliedCollision()
{
	//ALLIED CASE
	std::vector<std::shared_ptr<Character>> enemies;
	enemies = *entitydata->enemies;

	if (!enemies.empty())
	{
		for (int i = 0; i != enemies.size(); i++)
		{
			collision->CollideWithEntity(this->hit_box.getGlobalBounds(), enemies[i]->getHitBox().getGlobalBounds());
			if (collision->isCollide())
			{
				enemies[i]->takeDamage();
				collision->resetOutMtv();
				this->collide = true;
				return;
			}
		}
	}

	if (entitydata->boss)
	{
		collision->CollideWithEntity(this->hit_box.getGlobalBounds(), entitydata->boss->getHitBox().getGlobalBounds());
		if (collision->isCollide())
		{
			entitydata->boss->takeDamage();
			collision->resetOutMtv();
			this->collide = true;
			return;
		}
	}

	//WALLS

	updateWallsCollision();

	this->collide = collision->isCollide();
}

void Bullet::updateEnemyCollision()
{
	//PLAYER
	collision->CollideWithEntity(this->hit_box.getGlobalBounds(), entitydata->player->getHitBox().getGlobalBounds());
	if (collision->isCollide())
	{
		entitydata->player->takeDamage();
		collision->resetOutMtv();
		this->collide = true;
		return;
	}

	//PET
	if (entitydata->pet)
	{
		collision->CollideWithEntity(this->hit_box.getGlobalBounds(), entitydata->pet->getHitBox().getGlobalBounds());
		if (collision->isCollide())
		{
			entitydata->pet->takeDamage();
			collision->resetOutMtv();
			this->collide = true;
			return;
		}
	}

	//WALLS

	updateWallsCollision();

	this->collide = collision->isCollide();
}

void Bullet::updateWallsCollision()
{
	//WALLS
	collision->CollideWithWalls(this->hit_box.getGlobalBounds(), entitydata->map->findWalls(static_cast<int>(sprite.getPosition().x), static_cast<int>(sprite.getPosition().y)));
	collision->resetOutMtv();
}

void Bullet::updateRotate(sf::Vector2f vec_dir)
{
	const float PI = 3.14159265f;
	float deg = atan2(vec_dir.y, vec_dir.x) * 180.f / PI;

	this->sprite.setRotation(deg);
	this->hit_box.setRotation(deg);
}
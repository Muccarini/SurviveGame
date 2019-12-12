#include "Bullet.h"



Bullet::Bullet(sf::Texture txt)
{
	this->texture = txt;
	this->mov_speed = 1500;
	collideEnemy = false;
	collideWall = false;

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

	collisionEnemies(*entitydata->enemies);
	collisionWalls(entitydata->walls);

	float dX = sprite.getPosition().x - owner_pos.x;
	float dY = sprite.getPosition().y - owner_pos.y;
	float distance = sqrt(pow(dX, 2) + pow(dY, 2));

	rotate(dir);
}

void Bullet::setDir(sf::Vector2f owner_pos, sf::Vector2f mousePosView)
{
	this->owner_pos = owner_pos;

	this->sprite.setPosition(owner_pos);

	float dX = mousePosView.x - owner_pos.x;
	float dY = mousePosView.y - owner_pos.y;

	float lenght = sqrt(pow(dX, 2) + pow(dY, 2));

	sf::Vector2f normVect(dX / lenght, dY / lenght);

	dir = normVect;
}

void Bullet::initSprite()
{
	sprite.setTexture(texture);
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

void Bullet::collisionWalls(std::vector<sf::FloatRect> walls)
{
	collideWall = false;

	for (int i = 0; i != walls.size(); i++)
	{
		if (sat_test(hit_box.getGlobalBounds(), walls[i], &out_mtv))
		{
			collideWall = true;
		}
	}
}

void Bullet::collisionEnemies(std::vector<std::shared_ptr<Character>> enemies)
{
	for (int i = 0; i != enemies.size(); i++)
	{
		if (sat_test(hit_box.getGlobalBounds(), enemies[i]->getHitBox().getGlobalBounds(), &out_mtv))
		{
			enemies[i]->takeDamage();
			collideEnemy = true;
		}
	}
}

void Bullet::rotate(sf::Vector2f vec_dir)
{
	const float PI = 3.14159265f;
	float deg = atan2(vec_dir.y, vec_dir.x) * 180.f / PI;

	this->sprite.setRotation(deg);
	this->hit_box.setRotation(deg);
}
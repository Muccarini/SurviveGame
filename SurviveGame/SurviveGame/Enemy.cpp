#include "Enemy.h"


Enemy::Enemy(const sf::Texture& texture, const GridNode& grid, float grid_size) : _m(grid, max_distance)
{
	initVar();
	initSprite(grid, texture);
	initHitBox(grid_size);
	_m.setMaxDist(max_distance);
}

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::updateMove(const sf::Time& delta_time, sf::Vector2f target, float grid_size)
{
	this->sprite.move(_m.move(delta_time, getPosition(), target, move_vect, mov_speed));

	hit_box.setPosition(getPosition());
	setGridPosition(grid_size);
}

void Enemy::updateRotate(sf::Vector2f target)
{
	float dX = target.x - this->sprite.getPosition().x;
	float dY = target.y - this->sprite.getPosition().y;
	const float PI = 3.14159265f;
	float deg = atan2(dY, dX) * 180.f / PI;

	this->sprite.setRotation(deg + 90.f);
}

void Enemy::updateHud()
{
	hud.updateText(hp, getPosition());
}

void Enemy::initVar()
{
	mov_speed = 100;
	hp = 10;
}

void Enemy::initSprite(GridNode grid,const sf::Texture & texture)
{
	sprite.setTexture(texture);
	sprite.setScale(0.9f, 0.9f);
	int k = /*7;*/rand() % 17 + 1;//max 1920
	int j = /*6;*/rand() % 13 + 1;//max 1080
	GridLocation pos = { k , j };
	while (!grid.getGrid()[j][k].walkable)
	{
		j++;
		k++;
	}
	sprite.setPosition(32 + k * 64.f, 32 + j * 64.f);
	sprite.setOrigin(+34.f, +34.f);
	sprite.setTextureRect(sf::IntRect(0, 0, 68, 68));
}

void Enemy::initHitBox(float grid_size)
{
	this->hit_box.setSize(sf::Vector2f(60.f, 60.f));
	this->hit_box.setOutlineColor(sf::Color::Blue);
	this->hit_box.setFillColor(sf::Color::Transparent);
	this->hit_box.setScale(sprite.getScale());
	this->hit_box.setPosition(getPosition());
	this->hit_box.setOrigin(30, 30);

	setGridPosition(grid_size);
}

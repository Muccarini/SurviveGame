#include "Enemy.h"
#include <math.h>


Enemy::Enemy() 
{
	initSprite();
	initHitBox();
}


Enemy::~Enemy()
{
}

void Enemy::updateMove(sf::Time deltaTime, const std::shared_ptr<Character> target)
{
	float dX = target->getPosition().x - this->sprite.getPosition().x;
	float dY = target->getPosition().y - this->sprite.getPosition().y;

	float lenght = sqrt(pow(dX, 2) + pow(dY, 2));

	sf::Vector2f normVect(dX / lenght, dY / lenght);

	this->sprite.move((normVect.x * this->mov_speed * deltaTime.asSeconds()), (normVect.y * this->mov_speed * deltaTime.asSeconds()));
	hit_box.setPosition(getPosition());
}

void Enemy::updateRotate(const std::shared_ptr<Character> target)
{
	float dX = target->getPosition().x - this->sprite.getPosition().x;
	float dY = target->getPosition().y - this->sprite.getPosition().y;
	const float PI = 3.14159265f;
	float deg = atan2(dY, dX) * 180.f / PI;

	this->sprite.setRotation(deg + 90.f);
}

void Enemy::updateHud()
{
	hud_character.updateText(hp, getPosition());
}

void Enemy::update(std::shared_ptr<EntityData> entitydata)
{
	updateMove(entitydata->deltaTime, entitydata->target);
	updateRotate(entitydata->target);
	updateHud();

	collisionWalls(entitydata->walls);
	collisionEnemies(*entitydata->enemies);
}


void Enemy::initVar()
{
	mov_speed = 150;
	hp = 10;
}

void Enemy::initSprite()
{
	sprite.setTexture(textures.get(Textures::Enemy));
	sprite.setScale(0.9, 0.9);
	sprite.setPosition(rand() % 400 + 500.f , rand() % 400);
	sprite.setOrigin(+34.f, +34.f);
	sprite.setTextureRect(sf::IntRect(0, 0, 68, 68));
}

void Enemy::initHitBox()
{
	this->hit_box.setSize(sf::Vector2f(70.f, 70.f));
	this->hit_box.setOutlineColor(sf::Color::Transparent);
	this->hit_box.setOutlineThickness(3.f);
	this->hit_box.setFillColor(sf::Color::Transparent);
	this->hit_box.setScale(sprite.getScale());
	this->hit_box.setPosition(getPosition());
	this->hit_box.setOrigin(35, 35);
}


#include "Enemy.h"


Enemy::Enemy(const std::shared_ptr<EntityData> entitydata) : 
	_m(*entitydata->grid, target, max_distance, distance)
{
	this->entitydata = entitydata;

	initVar();
	initSprite();
	initHitBox();
	_m.setDist(distance);
	_m.setMaxDist(max_distance);
}

Enemy::Enemy() : _m(*entitydata->grid, target, max_distance, distance)
{
}


Enemy::~Enemy()
{
}

void Enemy::updateMove()
{
	this->_m.move(this->entitydata->deltaTime, &(this->sprite), this->entitydata->player->getPosition(), move_vect, mov_speed);
	this->target.x = this->entitydata->player->getPosition().x;
	this->target.y = this->entitydata->player->getPosition().y;

	hit_box.setPosition(getPosition());
	setGridPosition(this->entitydata->map->getGridSize());
}

void Enemy::updateRotate()
{
	float dX = entitydata->player->getPosition().x - this->sprite.getPosition().x;
	float dY = entitydata->player->getPosition().y - this->sprite.getPosition().y;
	const float PI = 3.14159265f;
	float deg = atan2(dY, dX) * 180.f / PI;

	this->sprite.setRotation(deg + 90.f);
}

void Enemy::updateHud()
{
	hud.updateText(hp, getPosition());
}

void Enemy::updateCollision()
{
	sf::Vector2f ent(0, 0);
	sf::Vector2f dir(0, 0);

	//PLAYER
	ent = this->collision->CollideWithEntity(entitydata->player->getHitBox().getGlobalBounds(), this->getHitBox().getGlobalBounds());
	sprite.move(-ent);
	if (ent.x != 0 || ent.y != 0)
		entitydata->player->takeDamage();
	collision->resetOutMtv();

	//PET
	if (entitydata->pet)
	{
		ent = this->collision->CollideWithEntity(entitydata->pet->getHitBox().getGlobalBounds(), this->getHitBox().getGlobalBounds());
		sprite.move(-ent);
		if (ent.x != 0 || ent.y != 0)
			entitydata->pet->takeDamage();
		collision->resetOutMtv();
	}

	//WALLS
	dir = this->collision->CollideWithWalls(this->getHitBox().getGlobalBounds(), entitydata->map->findWalls(static_cast<int>(sprite.getPosition().x), static_cast<int>(sprite.getPosition().y)));
 	sprite.move(dir);
	hit_box.setPosition(getPosition());
	collision->resetOutMtv();

	setGridPosition(this->entitydata->map->getGridSize());
}

void Enemy::update()
{
	updateCollision();
	updateMove();
	updateRotate();
	updateHud();
}

void Enemy::renderBullets(std::shared_ptr<sf::RenderWindow> target)
{
		/*for (int i = 0; i < bullets.size(); i++)
			bullets[i]->render(target);*/
}


void Enemy::initVar()
{
	mov_speed = 100;
	hp = 10;
	max_distance = 64;
}

void Enemy::initSprite()
{
	sprite.setTexture(entitydata->textures->get(Textures::Enemy));
	sprite.setScale(0.9f, 0.9f);
	int k = /*7;*/rand() % 17 + 1;//max 1920
	int j = /*6;*/rand() % 13 + 1;//max 1080
	GridLocation pos = { k , j };
	while (!this->entitydata->grid->getGrid()[j][k].walkable)
	{
		j++;
		k++;
	}
	sprite.setPosition(32 + k * 64.f, 32 + j * 64.f);
	sprite.setOrigin(+34.f, +34.f);
	sprite.setTextureRect(sf::IntRect(0, 0, 68, 68));
}

void Enemy::initHitBox()
{
	this->hit_box.setSize(sf::Vector2f(60.f, 60.f));
	this->hit_box.setOutlineColor(sf::Color::Blue);
	this->hit_box.setFillColor(sf::Color::Transparent);
	this->hit_box.setScale(sprite.getScale());
	this->hit_box.setPosition(getPosition());
	this->hit_box.setOrigin(30, 30);

	setGridPosition(this->entitydata->map->getGridSize());
}

void Enemy::takeDamage()
{// a seconda del tipo di proiettile da cui viene colpito take dmg
	this->hp--;
}


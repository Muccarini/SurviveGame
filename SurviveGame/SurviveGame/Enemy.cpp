#include "Enemy.h"


Enemy::Enemy(sf::Texture texture, GridNode grid, float grid_size) : _m(grid, max_distance, distance)
{
	initVar();
	initSprite(grid, texture);
	initHitBox(grid_size);
	_m.setDist(distance);
	_m.setMaxDist(max_distance);
}

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::updateMove(sf::Time deltaTime, sf::Vector2f target, float grid_size)
{
	this->sprite.move(_m.move(deltaTime, &(this->sprite), target, move_vect, mov_speed));

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

void Enemy::updateCollision(std::shared_ptr<PlayerT> player, std::shared_ptr<Pet> pet, std::vector<sf::FloatRect> walls, float grid_size)
{
	sf::Vector2f ent(0, 0);
	sf::Vector2f dir(0, 0);

	//PLAYER
	ent = this->collision->CollideWithEntity(player->getHitBox().getGlobalBounds(), this->getHitBox().getGlobalBounds());
	sprite.move(-ent);
	collision->resetOutMtv();

	//PET
	if (pet)
	{
		ent = this->collision->CollideWithEntity(pet->getHitBox().getGlobalBounds(), this->getHitBox().getGlobalBounds());
		sprite.move(-ent);
		if (ent.x != 0 || ent.y != 0)
			pet->takeDamage();
		collision->resetOutMtv();
	}

	//WALLS
	dir = this->collision->CollideWithWalls(this->getHitBox().getGlobalBounds(), walls);
 	sprite.move(dir);
	hit_box.setPosition(getPosition());
	collision->resetOutMtv();

	setGridPosition(grid_size);
}

void Enemy::renderBullets(std::shared_ptr<sf::RenderWindow> target)
{
}

void Enemy::initVar()
{
	mov_speed = 100;
	hp = 10;
	max_distance = 64;
}

void Enemy::initSprite(GridNode grid, sf::Texture texture)
{
	sprite.setTexture(texture);
	sprite.setScale(0.9f, 0.9f);
	int k = /*7;*/rand() % 17 + 1;//max 1920
	int j = /*6;*/rand() % 13 + 1;//max 1080
	GridLocation pos = { k , j };
	while (grid.getGrid()[j][k].walkable)
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

void Enemy::takeDamage()
{// a seconda del tipo di proiettile da cui viene colpito take dmg
	this->hp--;
}


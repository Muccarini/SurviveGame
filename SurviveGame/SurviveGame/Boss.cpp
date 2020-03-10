#include "Boss.h"

Boss::Boss(GridNode grid, sf::Texture texture) :
	_m(grid, max_distance, distance)
{
	initVar();
	initSprite(grid, texture);
	initHitBox();
	_m.setDist(distance);
	_m.setMaxDist(max_distance);
}

Boss::Boss()
{
}

Boss::~Boss()
{
}

void Boss::updateMove(sf::Time deltaTime, sf::Vector2f target, float grid_size)
{
	this->sprite.move(_m.move(deltaTime, &(this->sprite), target, move_vect, mov_speed));

	hit_box.setPosition(getPosition());
	setGridPosition(grid_size);
}

bool Boss::shooting(sf::Time deltaTime, sf::Vector2f target)
{
	ratio_clock -= deltaTime;

	if (isInRange(getPosition(), target) && !reloading)
	{
		if (ratio_clock < sf::seconds(0.f))
		{
			ratio_clock = ratio_cd;
			shoot = true;
			if (this->ammo)
				return true;
		}
		else
			shoot = false;
		return shoot;
	}
	else
		shoot = false;
	return shoot;
}

void Boss::updateRotate(sf::Vector2f target)
{
	float dX = target.x - this->sprite.getPosition().x;
	float dY = target.y - this->sprite.getPosition().y;
	const float PI = 3.14159265f;
	float deg = atan2(dY, dX) * 180.f / PI;

	this->sprite.setRotation(deg);
}

void Boss::updateReload(sf::Time deltaTime)
{
	if (ammo == 0)
	{
		reloading = true;
		reload_clock -= deltaTime;

		if (reload_clock < sf::seconds(0.f))
		{
			ammo = ammo_max;
			reload_clock = reload_cd;
			reloading = false;
		}
	}
}

void Boss::updateHud()
{
	hud.updateText(hp, getPosition());
}

void Boss::updateCollision(sf::FloatRect target, std::vector<sf::FloatRect> walls, float grid_size)
{
	sf::Vector2f dir(0.f, 0.f);
	sf::Vector2f ent(0.f, 0.f);

	ent = this->collision->CollideWithEntity(this->getHitBox().getGlobalBounds(), target);
	sprite.move(ent);

	if (ent != sf::Vector2f(0.f, 0.f))
		collision->resetOutMtv();

	dir = this->collision->CollideWithWalls(this->getHitBox().getGlobalBounds(), walls);
	sprite.move(dir);

	if (dir != sf::Vector2f(0.f, 0.f))
		collision->resetOutMtv();

	setGridPosition(grid_size);
}

bool Boss::isInRange(sf::Vector2f obj1, sf::Vector2f obj2)
{
	float dx = obj1.x - obj2.x;
	float dy = obj1.y - obj2.y;
	float lenght = sqrt(pow(dx, 2) + pow(dy, 2));

	if (fabs(lenght) < range)
		return true;
	else
		return false;
}

void Boss::takeDamage()
{
	this->hp--;
}

void Boss::initVar()
{
	mov_speed_default = 150;
	mov_speed = mov_speed_default;

	max_distance = 64;

	hp_max = 200;
	hp = hp_max;

	reload_cd = sf::seconds(2.f); //DA SCEGLIERE
	reload_clock = reload_cd;

	ammo_max = 200;  // DA SCEGLIERE
	ammo = ammo_max;

	ratio_cd = sf::seconds(1.f / 7.f); //DA SCEGLIERE
	ratio_clock = ratio_cd;

	reloading = false;

	range = 300;
}

void Boss::initSprite(GridNode grid, sf::Texture texture)
{
	sprite.setTexture(texture);
	sprite.setScale(1.5, 1.5);
	int k = /*7;*/rand() % 17 + 1;//max 1920
	int j = /*6;*/rand() % 13 + 1;//max 1080
	GridLocation pos = { k , j };
	while (!grid.getGrid()[j][k].walkable)
	{
		j++;
		k++;
	}
	sprite.setPosition(32 + k * 64.f, 32 + j * 64.f);
	sprite.setOrigin(+18, +16);
}

void Boss::initHitBox()
{
	hit_box.setSize(sf::Vector2f(36.f, 36.f));
	hit_box.setOutlineColor(sf::Color::Transparent);
	hit_box.setOutlineThickness(0.1f);
	hit_box.setFillColor(sf::Color::Transparent);
	hit_box.setScale(sprite.getScale());
	hit_box.setPosition(getPosition());
	hit_box.setOrigin(18, 16);
}

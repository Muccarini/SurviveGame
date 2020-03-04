#include "Boss.h"

Boss::Boss(std::shared_ptr<EntityData> entitydata) :
	_m(*entitydata->grid, target, max_distance, distance)
{
	this->entitydata = entitydata;

	initVar();
	initSprite();
	initHitBox();
	_m.setDist(distance);
	_m.setMaxDist(max_distance);
}

Boss::Boss() : _m(*entitydata->grid, target, max_distance, distance)
{
}

Boss::~Boss()
{
}

void Boss::update()
{
	updateMove();
	updateRotate();
	updateBullets();
	updateReload();
	updateHud();
	updateCollision();
}

void Boss::renderBullets(std::shared_ptr<sf::RenderWindow> target)
{
	for (int i = 0; i != bullets.size(); i++)
	{
		bullets[i]->render(target);
	}
}

void Boss::updateMove()
{
	this->sprite.move(_m.move(this->entitydata->deltaTime, &(this->sprite), this->entitydata->player->getPosition(), move_vect, mov_speed));
	this->target.x = this->entitydata->player->getPosition().x;
	this->target.y = this->entitydata->player->getPosition().y;

	hit_box.setPosition(getPosition());
	setGridPosition(this->entitydata->map->getGridSize());
}

void Boss::updateBullets()
{
	updateShooting();

	if (shooting && getAmmo())
	{
		std::shared_ptr<Bullet>bullet(new Bullet(BulletOwner::Boss, entitydata));
		ammo--;
		bullets.emplace_back(bullet);
		bullet->calculateDir();
	}

	for (unsigned int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->update();
		if (bullets[i]->isCollide())
			bullets.erase(bullets.begin() + i);
	}
}

void Boss::updateRotate()
{
	float dX = entitydata->player->getPosition().x - this->sprite.getPosition().x;
	float dY = entitydata->player->getPosition().y - this->sprite.getPosition().y;
	const float PI = 3.14159265f;
	float deg = atan2(dY, dX) * 180.f / PI;

	this->sprite.setRotation(deg);
}

void Boss::updateReload()
{
	if (ammo == 0)
	{
		reloading = true;
		reload_clock -= entitydata->deltaTime;

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

void Boss::updateCollision()
{
	sf::Vector2f dir(0.f, 0.f);
	sf::Vector2f ent(0.f, 0.f);

	ent = this->collision->CollideWithEntity(this->getHitBox().getGlobalBounds(), entitydata->player->getHitBox().getGlobalBounds());
	sprite.move(ent);

	if (ent != sf::Vector2f(0.f, 0.f))
		collision->resetOutMtv();

	dir = this->collision->CollideWithWalls(this->getHitBox().getGlobalBounds(), entitydata->map->findWalls(static_cast<int>(sprite.getPosition().x), static_cast<int>(sprite.getPosition().y)));
	sprite.move(dir);

	if (dir != sf::Vector2f(0.f, 0.f))
		collision->resetOutMtv();

	setGridPosition(this->entitydata->map->getGridSize());
}


void Boss::updateShooting()
{
	ratio_clock -= entitydata->deltaTime;

	if (isInRange(entitydata->boss->getPosition(), entitydata->player->getPosition()) && !reloading)
	{
		if (ratio_clock < sf::seconds(0.f))
		{
			ratio_clock = ratio_cd;
			shooting = true;
		}
		else
			shooting = false;
	}
	else
		shooting = false;
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

void Boss::initSprite()
{
	sprite.setTexture(entitydata->textures->get(Textures::Boss));
	sprite.setScale(1.5, 1.5);
	int k = /*7;*/rand() % 17 + 1;//max 1920
	int j = /*6;*/rand() % 13 + 1;//max 1080
	GridLocation pos = { k , j };
	while (!this->entitydata->grid->getGrid()[j][k].walkable)
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

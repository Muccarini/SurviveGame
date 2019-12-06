#include "Boss.h"

Boss::Boss(sf::Texture texture_character, sf::Texture texture_bullet)
{
	this->texture = texture_character;
	this->texture_bullet = texture_bullet;

	initVar();
	initSprite();
	initHitBox();
}

Boss::Boss()
{
}

Boss::~Boss()
{
}

void Boss::update(std::shared_ptr<EntityData> entitydata)
{
	if (!isInRange(entitydata->boss->getPosition(), entitydata->player->getPosition()))
	{
		updateMove(entitydata->deltaTime, entitydata->player);
	}
	updateRotate(entitydata->player);
	updateBullets(entitydata);
	updateHud();

	updateCollision(entitydata);
}

void Boss::renderBullets(std::shared_ptr<sf::RenderWindow> target)
{
	for (int i = 0; i != bullets.size(); i++)
	{
		bullets[i]->render(target);
	}
}

void Boss::updateMove(sf::Time deltaTime, std::shared_ptr<Character> target)
{
	float dX = target->getPosition().x - this->sprite.getPosition().x;
	float dY = target->getPosition().y - this->sprite.getPosition().y;

	float lenght = sqrt(pow(dX, 2) + pow(dY, 2));

	sf::Vector2f normVect(dX / lenght, dY / lenght);

	this->sprite.move(normVect.x * this->mov_speed * deltaTime.asSeconds(), normVect.y * this->mov_speed * deltaTime.asSeconds());
	hit_box.setPosition(getPosition());
}

void Boss::updateBullets(std::shared_ptr<EntityData> entitydata)
{
	if (isShooting(entitydata) && getAmmo())
	{
		std::shared_ptr<Bullet>bullet(new Bullet(entitydata->boss, texture_bullet));
		ammo--;
		bullets.emplace_back(bullet);
		bullet->setDir(entitydata->boss->getPosition(), entitydata->player->getPosition());
	}

	for (int i = 0; i != bullets.size(); i++)
	{
		bullets[i]->update(entitydata);
		if (bullets[i]->isCollideEnemy() || bullets[i]->isCollideWall())
			bullets.erase(bullets.begin() + i);
	}
}

void Boss::updateRotate(std::shared_ptr<Character> target)
{
	float dX = target->getPosition().x - this->sprite.getPosition().x;
	float dY = target->getPosition().y - this->sprite.getPosition().y;
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
			reload_clock = sf::seconds(1.f);
			reloading = false;
		}
	}
}

void Boss::updateHud()
{
	hud.updateText(hp, getPosition());
}

void Boss::updateCollision(std::shared_ptr<EntityData> entitydata)
{
	sf::Vector2f dir(0, 0);

	dir = collision->isCollideWith(entitydata->boss, entitydata->player);
	if (dir.x == 0 && dir.y == 0)
		takeDamage();

	dir += collision->isCollideWithWalls(entitydata->boss, entitydata->walls);

	sprite.move((dir.x * this->mov_speed* entitydata->deltaTime.asSeconds()), dir.y * this->mov_speed* entitydata->deltaTime.asSeconds());
}

bool Boss::isShooting(std::shared_ptr<EntityData> entitydata)
{
	ratio_clock -= entitydata->deltaTime;

	if (isInRange(entitydata->boss->getPosition(), entitydata->player->getPosition()) && !reloading)
	{
		if (ratio_clock < sf::seconds(0.f))
		{
			ratio_clock = ratio;
			return true;
		}
	}
	return false;
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
	mov_speed_max = 150;
	mov_speed = mov_speed_max;

	hp_max = 1000;
	hp = hp_max;

	reload = sf::seconds(1.f); //DA SCEGLIERE
	reload_clock = reload;

	ammo_max = 200;  // DA SCEGLIERE
	ammo = ammo_max;

	ratio = sf::seconds(1.f / 16.666); //DA SCEGLIERE
	ratio_clock = ratio;

	reloading = false;
	allied = false;
	range = 200;
}

void Boss::initSprite()
{
	sprite.setTexture(texture);
	sprite.setScale(1.5, 1.5);
	sprite.setPosition(600.f, 600.f);
	sprite.setOrigin(+18, +16);
}

void Boss::initHitBox()
{
	hit_box.setSize(sf::Vector2f(25.f, 25.f));
	hit_box.setOutlineColor(sf::Color::Transparent);
	hit_box.setOutlineThickness(10.f);
	hit_box.setFillColor(sf::Color::Transparent);
	hit_box.setScale(sprite.getScale());
	hit_box.setPosition(getPosition());
	hit_box.setOrigin(+18, +13);
}

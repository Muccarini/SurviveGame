#include "PlayerT.h"

PlayerT::PlayerT(sf::Texture txt_p, sf::Texture txt_b)
{
	this->texture = txt_p;
	this->texture_bullet = txt_b;

	initVar();
	initSprite();
	initHitBox();
}

PlayerT::PlayerT()
{
}


PlayerT::~PlayerT()
{
}

void PlayerT::update(std::shared_ptr<EntityData> entitydata)
{
	updateMove(entitydata->deltaTime);
	updateBullets(entitydata);
	updateRotate(entitydata->mouse_pos_view);
	updateReload(entitydata->deltaTime);
	updateHud();
	updateCollision(entitydata);
}

void PlayerT::updateMove(sf::Time deltaTime)
{
	sf::Vector2f dir(0, 0);

	bool w_is_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	bool a_is_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	bool s_is_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
	bool d_is_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

	if (w_is_pressed)
	{
		dir.y = -1;
	}

	if (a_is_pressed)
	{
		dir.x = -1;
	}

	if (s_is_pressed)
	{
		dir.y = +1;
	}

	if (d_is_pressed)
	{
		dir.x = +1;
	}

	updateDash(dir, deltaTime);

	this->sprite.move((dir.x * this->mov_speed* deltaTime.asSeconds()) , dir.y * this->mov_speed* deltaTime.asSeconds());
	hit_box.setPosition(getPosition());
}

void PlayerT::updateBullets(std::shared_ptr<EntityData> entitydata)
{
	if (isShooting(entitydata->deltaTime) && getAmmo())
	{
		std::shared_ptr<Bullet>bullet(new Bullet(entitydata->player, texture_bullet));
		ammo--;
		bullets.emplace_back(bullet);
		bullet->setDir(entitydata->player->getPosition(), entitydata->mouse_pos_view);
	}

	if (!bullets.empty())
	{
		for (int i = 0; i != bullets.size(); i++)
		{
			bullets[i]->update(entitydata);
			if (bullets[i]->isCollide())
				bullets.erase(bullets.begin() + i);
		}
	}
}

void PlayerT::updateRotate(sf::Vector2f mousePosView)
{
	float dX = mousePosView.x - getPosition().x;
	float dY = mousePosView.y - getPosition().y;
	const float PI = 3.14159265f;
	float deg = atan2(dY, dX) * 180.f / PI;

	this->sprite.setRotation(deg + 360.f);
}

void PlayerT::updateReload(sf::Time deltaTime)
{
	if (!reloading)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && ammo != ammo_max)
			reloading = true;
	}

	if (ammo == 0 || reloading)
	{
		reload_clock -= deltaTime;
		if (reload_clock < sf::seconds(0.f))
		{
			ammo = ammo_max;
			reload_clock = reload;
			reloading = false;
		}
	}
}

void PlayerT::updateDash(sf::Vector2f dir, sf::Time deltaTime)
{
	bool space_is_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

	if (space_is_pressed && !is_dashing)
	{
		sprite.setPosition(getPosition().x + (dir.x * 160), (dir.y * 160) + getPosition().y);
		is_dashing = true;
	}
	if (is_dashing && dash_cd > 0)
	{
		dash_cd -= deltaTime.asSeconds();
		if (dash_cd < 0)
		{
			is_dashing = false;
			dash_cd = 10;
		}
	}
}

void PlayerT::updateHud()
{
	hud.updateText(getAmmo(), getHp(), this->dash_cd, getPosition());
}

void PlayerT::updateCollision(std::shared_ptr<EntityData> entitydata)
{
	sf::Vector2f dir(0, 0);

	std::vector<std::shared_ptr<Character>> enemies;
	enemies = *entitydata->enemies;

	for(int i = 0; i != enemies.size(); i++)
	{
	dir = this->collision->CollideWithEntity(this->hit_box.getGlobalBounds(), enemies[i]->getHitBox().getGlobalBounds());
	if (dir.x != 0 && dir.y != 0)
		takeDamage();
	}
	dir = sf::Vector2f(0.f, 0.f);
	dir += this->collision->CollideWithWalls(this->hit_box.getGlobalBounds(), entitydata->walls);

	sprite.move(dir);
	collision->resetOutMtv();
}

bool PlayerT::isShooting(sf::Time deltaTime)
{
	ratio_clock -= deltaTime;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !reloading)
	{
		if (ratio_clock < sf::seconds(0.f))
		{
			ratio_clock = ratio;
			return true;
		}
	}
	return false;
}

void PlayerT::renderBullets(std::shared_ptr<sf::RenderWindow> target)
{
	for (int i=0; i != bullets.size(); i++)
	{
		bullets[i]->render(target);
	}
}


void PlayerT::initVar()
{
	mov_speed_max = 200;
	mov_speed = mov_speed_max;

	hp = 100;

	reload = sf::seconds(1.f);
	reload_clock = reload;

	ammo_max = 200;
	ammo = ammo_max;

	ratio = sf::seconds(1.f / 16.666f);
	ratio_clock = ratio;

	allied = true;

	this->dash_speed = 1000;
	this->dash_cd = 10.f;
	this->is_dashing = false;
}

void PlayerT::initSprite()
{
	sprite.setTexture(texture); //TEXTURE
	sprite.setScale(0.3f, 0.3f);                              //SCALE
	sprite.setPosition(600.f, 600.f);                       //POS
	sprite.setOrigin(92, 120);                              //ORIGIN
}

void PlayerT::initHitBox()
{
	hit_box.setSize(sf::Vector2f(100.f, 100.f));     //SIZE
	hit_box.setOutlineColor(sf::Color::Transparent); //COLOR
	hit_box.setOutlineThickness(3.f);
	hit_box.setFillColor(sf::Color::Transparent);
	hit_box.setScale(sprite.getScale());             //SCALE
	hit_box.setPosition(getPosition());              //POS
	hit_box.setOrigin(45, 60);                       //ORIGIN
}

void PlayerT::takeDamage()
{
	this->hp--;
}

#include "PlayerT.h"

PlayerT::PlayerT(const std::shared_ptr<EntityData> entitydata, Textures::ID id, StrategyFight* stf) : id(id)
{
	this->entitydata = entitydata;
	setStrategyFight(stf);
	setType();
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

void PlayerT::update()
{
	updateMove();
	updateBullets();
	updateRotate();
	updateReload();
	updateHud();
	updateCollision();
}

void PlayerT::updateMove()
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

	updateDash(dir);
	updateMovSpeed();

	hit_box.setPosition(getPosition() + sf::Vector2f((dir.x * this->mov_speed* entitydata->deltaTime.asSeconds()), dir.y * this->mov_speed* entitydata->deltaTime.asSeconds()));
	updateCollision();
	this->sprite.move((dir.x * this->mov_speed* entitydata->deltaTime.asSeconds()) , dir.y * this->mov_speed* entitydata->deltaTime.asSeconds());
}

void PlayerT::updateBullets()
{
	updateShooting();

	if (shooting && getAmmo())
	{
		this->stf->shot(bullets, this->entitydata);
		ammo--;
	}

	if (!bullets.empty())
	{
		for (unsigned int i = 0; i < bullets.size(); i++)
		{
			bullets[i]->update();
			if (bullets[i]->isCollide())
				bullets.erase(bullets.begin() + i);
		}
	}
}

void PlayerT::updateRotate()
{
	float dX = entitydata->mouse_pos_view.x - getPosition().x;
	float dY = entitydata->mouse_pos_view.y - getPosition().y;
	const float PI = 3.14159265f;
	float deg = atan2(dY, dX) * 180.f / PI;

	this->sprite.setRotation(deg + 360.f);
}

void PlayerT::updateReload()
{
	if (!reloading)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && ammo != ammo_max)
			reloading = true;
	}

	if (ammo == 0 || reloading)
	{
		reload_clock -= entitydata->deltaTime;
		if (reload_clock < sf::seconds(0.f))
		{
			ammo = ammo_max;
			reload_clock = reload_cd;
			reloading = false;
		}
	}
}

void PlayerT::updateDash(sf::Vector2f dir)
{
	bool space_is_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

	if (space_is_pressed && !is_dashing)
	{
		hit_box.setPosition(getPosition().x + (dir.x * 160), (dir.y * 160) + getPosition().y);
		collision->CollideWithWalls(this->hit_box.getGlobalBounds(), entitydata->map->findWalls(static_cast<int>(hit_box.getGlobalBounds().left), static_cast<int>(hit_box.getGlobalBounds().top)));
		if (!this->collision->isCollide())
		{
			is_dashing = true;
			this->sprite.setPosition(hit_box.getGlobalBounds().left, hit_box.getGlobalBounds().top);
			
		}
		else
			hit_box.setPosition(getPosition());
	}
	if (is_dashing && dash_clock > 0)
	{
		dash_clock -= entitydata->deltaTime.asSeconds();
		if (dash_clock < 0)
		{
			is_dashing = false;
			dash_clock = dash_cd;
		}
	}
}

void PlayerT::updateMovSpeed()
{
	if (this->mov_speed != this->mov_speed_default)
	{
		this->sprite.setTexture(this->entitydata->textures->get(Textures::PersonaggioMS));
		this->ms_clock -= entitydata->deltaTime.asSeconds();
	}

	if (ms_clock < 0.f)
	{
		this->ms_clock = this->ms_cd;
		this->mov_speed = this->mov_speed_default;
		this->sprite.setTexture(this->entitydata->textures->get(this->id));
	}
		
}

void PlayerT::updateHud()
{
	hud.updateText(getAmmo(), getHp(), this->dash_clock, getPosition());
}

void PlayerT::updateCollision()
{
	sf::Vector2f dir(0, 0);
	sf::Vector2f ent(0, 0);

	std::vector<std::shared_ptr<Character>> enemies;
	enemies = *entitydata->enemies;

	for(int i = 0; i != enemies.size(); i++)
	{
	ent = this->collision->CollideWithEntity(this->hit_box.getGlobalBounds(), enemies[i]->getHitBox().getGlobalBounds());
	if (ent.x != 0 || ent.y != 0)
		takeDamage();
	}
	sprite.move(ent);
	hit_box.setPosition(getPosition());
	collision->resetOutMtv();

	//WALLS
	dir = this->collision->CollideWithWalls(this->hit_box.getGlobalBounds(), entitydata->map->findWalls(static_cast<int>(getPosition().x), static_cast<int>(getPosition().y)));

	this->collision->setPreMtv(this->collision->getOutMtv());
	sprite.move(dir);
	hit_box.setPosition(getPosition());
	collision->resetOutMtv();
	setGridPosition(entitydata->map->getGridSize());
}

void PlayerT::updateDataPlayer()
{
}

void PlayerT::updateShooting()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !reloading)
	{
		ratio_clock -= entitydata->deltaTime;

		if (ratio_clock < sf::seconds(0.f))
		{
			ratio_clock = ratio_cd;
			this->shooting = true;
		}
		else
			shooting = false;
	}
	else
		shooting = false;
}

void PlayerT::setStrategyFight(StrategyFight* stf)
{
	this->stf = stf;
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
	mov_speed_default = 200;
	mov_speed = mov_speed_default;

	hp_max = 100;
	hp = hp_max;

	reload_cd = sf::seconds(1.f);
	reload_clock = reload_cd;

	ammo_max = 200;
	ammo = ammo_max;

	//ratio_cd = sf::seconds(1.f / 16.666f);
	ratio_cd = this->stf->getRatio();
	ratio_clock = ratio_cd;

	this->dash_speed = 1000;
	this->dash_cd = 10.f;
	this->dash_clock = dash_cd;
	this->is_dashing = false;

	this->ms_cd = 3.f;
	this->ms_clock = ms_cd;
}

void PlayerT::initSprite()
{
	sprite.setTexture(this->entitydata->textures->get(this->id));       //TEXTURE
	sprite.setScale(0.3f, 0.3f);        //SCALE
	sprite.setPosition(600.f, 600.f); //POS
	sprite.setOrigin(92, 120);        //ORIGIN
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

void PlayerT::setType()
{
	switch (this->id)
	{
	case(Textures::ID::ShotgunP):
		this->type = CharacterType::Shotgun;
		break;
	case(Textures::ID::RifleP):
		this->type = CharacterType::Rifle;
		break;
	case(Textures::ID::HandgunP):
		this->type = CharacterType::Handgun;
		break;
	}
}

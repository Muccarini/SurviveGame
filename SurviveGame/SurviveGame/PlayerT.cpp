#include "PlayerT.h"

PlayerT::PlayerT()
{
}


PlayerT::~PlayerT()
{
}

void PlayerT::update(std::shared_ptr<EntityData> entitydata)
{
	updateMove(entitydata->deltaTime);
	updateRotate(entitydata->mouse_pos_view);
	updateReload(entitydata->deltaTime);
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && ammo != max_ammo)
			reloading = true;
	}
	if (ammo == 0 || reloading)
	{
		reload_clock -= deltaTime;
		if (reload_clock < sf::seconds(0.f))
		{
			ammo = max_ammo;
			reload_clock = sf::seconds(1.f);
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

void PlayerT::initSprite()
{
	sprite.setTexture(texture);       //TEXTURE
	sprite.setScale(0.3, 0.3);        //SCALE
	sprite.setPosition(600.f, 600.f); //POS
	sprite.setOrigin(92, 120);        //ORIGIN
}

void PlayerT::initHitBox()
{
	hit_box.setSize(sf::Vector2f(100.f, 100.f));     //SIZE
	hit_box.setOutlineColor(sf::Color::Transparent); //COLOR
	hit_box.setOutlineThickness(3.f);
	hit_box.setFillColor(sf::Color::Transparent);
	hit_box.setScale(sprite.getScale());            //SCALE
	hit_box.setPosition(getPosition());              //POS
	hit_box.setOrigin(45, 60);                       //ORIGIN
}

#include "Player.h"
#include <math.h>
#include <algorithm>


Player::Player()
{
	hp             = 100;
	mov_speed      = 200;
	reload_time    = sf::seconds(1.f);
	reload_counter = reload_time;
	max_ammo       = 200;
	ammo           = max_ammo;
	ratio          = sf::seconds(1.f / 20.f);

	texture.loadFromFile("Sources/Top_Down_Survivor/rifle/move/survivor-move_rifle_0.png");
	initSprite();
	initHitBox();
}

Player::~Player()
{
}

void Player::initSprite()
{
	_sprite.setTexture(texture);       //TEXTURE
	_sprite.setScale(0.3, 0.3);        //SCALE
	_sprite.setPosition(600.f, 600.f); //POS
	_sprite.setOrigin(92, 120);        //ORIGIN
}

void Player::initHitBox()
{
	hit_box.setSize(sf::Vector2f(207.f, 207.f));     //SIZE
	hit_box.setOutlineColor(sf::Color::Transparent); //COLOR
	hit_box.setOutlineThickness(3.f);
	hit_box.setFillColor(sf::Color::Transparent);
	hit_box.setScale(0.15, 0.15);                    //SCALE
	hit_box.setPosition(getPosition());              //POS
	hit_box.setOrigin(_sprite.getOrigin());          //ORIGIN
}

void Player::move(sf::Time deltaTime)
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

	this->_sprite.move(dir * this->mov_speed * deltaTime.asSeconds());
	hit_box.setPosition(getPosition());
	}

void Player::rotate(sf::Vector2f mousePosView)
{
	float dX = mousePosView.x - getPosition().x;
	float dY = mousePosView.y - getPosition().y;
	const float PI = 3.14159265f;
	float deg = atan2(dY, dX) * 180.f / PI;

	this->_sprite.setRotation(deg + 360.f);
}

void Player::reload(sf::Time deltaTime) //TODO VOGLIO FARE LA CLASSE ANIMATION E METTERE L'ANIMAZIONE DEL RELOAD
{ 
	if(!is_reloading)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && ammo != max_ammo)
			is_reloading = true;
	}
	if (ammo == 0 || is_reloading)
	{
		reload_counter -= deltaTime;
			if (reload_counter < sf::seconds(0.f))
			{
				ammo = max_ammo;
				reload_counter = sf::seconds(1.f);
				is_reloading = false;
			}
	}
}

bool Player::isShooting(sf::Time deltaTime)
{
	ratio -= deltaTime;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !is_reloading)
	{
		if (ratio < sf::seconds(0.f))
		{
			ratio = sf::seconds(1.f / 16.666);
			return true;
		}
	}
	return false;
}

void Player::update(sf::Time deltaTime, sf::Vector2f mousePosView, std::vector<sf::FloatRect> collision, std::vector<std::shared_ptr<Enemy>> enemies)
{      
		move(deltaTime);
		rotate(mousePosView);
		reload(deltaTime);

		gui.updateText(ammo, hp, getPosition());

		//COLLISION MURI
		for (int i = 0 ; i != collision.size(); i++)
		{
			if (sat_test(hit_box.getGlobalBounds(), collision[i], &out_mtv))
			{
				_sprite.move(out_mtv);
			}
		}

		//COLLISION SUI NEMICI
		for (int i = 0; i != enemies.size(); i++)
		{
				if (sat_test(hit_box.getGlobalBounds(), enemies[i]->hit_box.getGlobalBounds(), &out_mtv))
				{
					_sprite.move(out_mtv);
					hp = hp - 1;
				}
		}
}
#include "Player.h"
#include <math.h>
#include <algorithm>


Player::Player()
{
	mov_speed = 200;
	reload_time = sf::seconds(1.5);
	ammo = 200;

	//TEXTURE
	texture.loadFromFile("Sources/Top_Down_Survivor/rifle/move/survivor-move_rifle_0.png");
	_sprite.setTexture(texture);

	hit_box.setSize(sf::Vector2f(207.f, 207.f));

	//COLOR
	hit_box.setOutlineColor(sf::Color::Transparent);
	hit_box.setOutlineThickness(3.f);
	hit_box.setFillColor(sf::Color::Transparent);
	//SCALE
	_sprite.setScale(0.3, 0.3);
	hit_box.setScale(0.15, 0.15);
	//POSITION
	_sprite.setPosition(300.f, 300.f);
	hit_box.setPosition(getPosition());
	//ORIGIN
	_sprite.setOrigin(92, 120);
	hit_box.setOrigin(_sprite.getOrigin());
}

Player::~Player()
{
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

bool Player::isShooting()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		return true;
	return false;
}

void Player::update(sf::Time deltaTime, sf::Vector2f mousePosView, std::vector<sf::FloatRect> collision, std::vector<std::shared_ptr<Enemy>> enemies)
{      
	    //MOVE (IF WASD)
		move(deltaTime);

		//ROTATION
		rotate(mousePosView);

		 //COLLISION SUI MURI
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
				}
		}
}
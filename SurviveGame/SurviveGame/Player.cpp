#include "Player.h"
#include <math.h>
#include <algorithm>


Player::Player()
{
	mov_speed = 200;
	_textures.load(Textures::Personaggio, "Sources/Top_Down_Survivor/rifle/move/survivor-move_rifle_0.png");
	_sprite.setTexture(_textures.get(Textures::Personaggio));
	hit_box.setRadius(_sprite.getGlobalBounds().width /3.f);
	hit_box.setOutlineColor(sf::Color::Magenta);
	hit_box.setOutlineThickness(3.f);
	hit_box.setFillColor(sf::Color::Transparent);
	_sprite.setScale(0.3f, 0.3f);
	hit_box.setScale(_sprite.getScale());
	_sprite.setPosition(300.f, 300.f);
	hit_box.setPosition(getPosition());
	_sprite.setOrigin(90, 110);
	hit_box.setOrigin(_sprite.getOrigin());

}

Player::~Player()
{
}

void Player::move(sf::Time deltaTime, sf::FloatRect collision) // TODO// cambiare mov_speed in movSpeed
{
	/*	sf::Vector2f vectorMov(0.f, 0.f);

		bool w_is_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
		bool a_is_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
		bool s_is_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
		bool d_is_pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

		if (w_is_pressed && !Intersect(hit_box, collision))
		{
			vectorMov.x = 0.f;
			vectorMov.y = 0.f;
			vectorMov.y = -mov_speed;
			_sprite.move(vectorMov* deltaTime.asSeconds());

			hit_box.setPosition(getPosition());
			sf::Vector2f curr_pos = _sprite.getPosition();
			move_vect = (curr_pos - old_pos);
		}

		if (a_is_pressed && !Intersect(hit_box, collision))
		{
			vectorMov.x = 0.f;
			vectorMov.y = 0.f;
			vectorMov.x = -mov_speed;
			_sprite.move(vectorMov * deltaTime.asSeconds());

			hit_box.setPosition(getPosition());
			sf::Vector2f curr_pos = _sprite.getPosition();
			move_vect = (curr_pos - old_pos);
		}

		if (s_is_pressed && !Intersect(hit_box, collision))
		{
			vectorMov.x = 0.f;
			vectorMov.y = 0.f;
			vectorMov.y = mov_speed;
			_sprite.move(vectorMov * deltaTime.asSeconds());

			hit_box.setPosition(getPosition());
			sf::Vector2f curr_pos = _sprite.getPosition();
			move_vect = (curr_pos - old_pos);
		}

		if (d_is_pressed && !Intersect(hit_box, collision))
		{
			vectorMov.x = 0.f;
			vectorMov.y = 0.f;
			vectorMov.x = mov_speed;
			_sprite.move(vectorMov * deltaTime.asSeconds());

			hit_box.setPosition(getPosition());
			sf::Vector2f curr_pos = _sprite.getPosition();
			move_vect = (curr_pos - old_pos);
		}*/
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

	if (Intersect(hit_box, collision))
	{
		if (move_vect.x = 0)
			dir.x = 0;
		else
			dir.y = 0;
	}

	this->_sprite.move(dir * this->mov_speed * deltaTime.asSeconds());

	hit_box.setPosition(getPosition());
	sf::Vector2f curr_pos = _sprite.getPosition();
	move_vect = (curr_pos - old_pos);
	}

void Player::rotate(sf::Vector2f mousePosView)
{
	float dX = mousePosView.x - getPosition().x;
	float dY = mousePosView.y - getPosition().y;
	const float PI = 3.14159265f;
	float deg = atan2(dY, dX) * 180.f / PI;

	this->_sprite.setRotation(deg + 360.f);
}

void Player::update(sf::Time deltaTime, sf::Vector2f mousePosView, sf::FloatRect collision)
{
		old_pos = _sprite.getPosition();
		move(deltaTime,collision);
		if(Intersect(hit_box, collision))
	{
		_sprite.setPosition(getPosition() - move_vect);
		hit_box.setPosition(getPosition());
	}

	rotate(mousePosView);
	

}

bool Player::Intersect(sf::CircleShape hit_box, sf::FloatRect collision)
{
	sf::Vector2f rect_center((collision.left + collision.width / 2), (collision.top + collision.height / 2));

	sf::Vector2f circleDistance;
	float cornerDistance_sq;

	circleDistance.x = abs(hit_box.getPosition().x - rect_center.x);
	circleDistance.y = abs(hit_box.getPosition().y - rect_center.y);

	if (circleDistance.x * 2 > (collision.width / 2 + hit_box.getRadius())) { return false; }
	if (circleDistance.y * 2> (collision.height / 2 + hit_box.getRadius())) { return false; }

	if (circleDistance.x * 2 <= (collision.width / 2)) { return true; }
	if (circleDistance.y * 2 <= (collision.height / 2)) { return true; }

	cornerDistance_sq = (pow((circleDistance.x - collision.width / 2),2)) + pow((circleDistance.y - collision.height / 2), 2);
	
	
	return (cornerDistance_sq * 2<= pow(hit_box.getRadius(), 2));
}


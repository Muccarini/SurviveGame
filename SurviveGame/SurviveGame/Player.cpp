#include "Player.h"
#include <math.h>
#include <algorithm>


Player::Player()
{
	mov_speed = 200;
	_textures.load(Textures::Personaggio, "Sources/Top_Down_Survivor/rifle/move/survivor-move_rifle_0.png");
	_sprite.setTexture(_textures.get(Textures::Personaggio));
	hit_box.setSize(sf::Vector2f(150.f,150.f));

	//COLOR
	hit_box.setOutlineColor(sf::Color::Red);
	hit_box.setOutlineThickness(3.f);
	hit_box.setFillColor(sf::Color::Transparent);
	//SCALE
	_sprite.setScale(0.3f, 0.3f);
	hit_box.setScale(_sprite.getScale());
	//POSITION
	_sprite.setPosition(300.f, 300.f);
	hit_box.setPosition(getPosition());
	//ORIGIN
	_sprite.setOrigin(92, 121);
	hit_box.setOrigin(89, 118);

}

Player::~Player()
{
}

void Player::move(sf::Time deltaTime, sf::FloatRect collision)
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
		move(deltaTime, collision);

		if (sat_test(hit_box.getGlobalBounds(), collision, &out_mtv))
			_sprite.move(out_mtv);

	rotate(mousePosView);
	

}

bool Player::sat_test(const sf::FloatRect &rectSp1, const sf::FloatRect &rectSp2, sf::Vector2f *out_mtv)
{

	float proj_x, proj_y, overlap_x, overlap_y;

	// test overlap in x axis
	proj_x = std::max(rectSp1.left + rectSp1.width, rectSp2.left + rectSp2.width) - std::min(rectSp1.left, rectSp2.left);
	if (proj_x < rectSp1.width + rectSp2.width) {
		if (out_mtv) {
			// calculate mtv in x
			overlap_x = rectSp1.width + rectSp2.width - proj_x;
		}
		// test overlap in y axis
		proj_y = std::max(rectSp1.top + rectSp1.height, rectSp2.top + rectSp2.height) - std::min(rectSp1.top, rectSp2.top);
		if (proj_y < rectSp1.height + rectSp2.height) {
			if (out_mtv) {
				// calculate mtv in y
				overlap_y = rectSp1.height + rectSp2.height - proj_y;
				out_mtv->x = out_mtv->y = 0;

				// choose minimun overlap
				if (overlap_x < overlap_y) {
					out_mtv->x = overlap_x * (rectSp1.left < rectSp2.left ? -1 : 1);
				}
				else {
					out_mtv->y = overlap_y * (rectSp1.top < rectSp2.top ? -1 : 1);
				}
			}
			return true;
		}
	}
	return false;
}

//bool Player::Intersect(sf::CircleShape hit_box, sf::FloatRect collision)
//{
//	sf::Vector2f rect_center((collision.left + collision.width / 2), (collision.top + collision.height / 2));
//
//	sf::Vector2f circleDistance;
//	float cornerDistance_sq;
//
//	circleDistance.x = abs(hit_box.getPosition().x - rect_center.x);
//	circleDistance.y = abs(hit_box.getPosition().y - rect_center.y);
//
//	if (circleDistance.x * 2 > (collision.width / 2 + hit_box.getRadius())) { return false; }
//	if (circleDistance.y * 2> (collision.height / 2 + hit_box.getRadius())) { return false; }
//
//	if (circleDistance.x * 2 <= (collision.width / 2)) { return true; }
//	if (circleDistance.y * 2 <= (collision.height / 2)) { return true; }
//
//	cornerDistance_sq = (pow((circleDistance.x - collision.width / 2),2)) + pow((circleDistance.y - collision.height / 2), 2);
//	
//	
//	return (cornerDistance_sq * 2<= pow(hit_box.getRadius(), 2));
//}


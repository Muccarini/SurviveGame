//#include "Boss.h"
//
//
//
//Boss::Boss()
//{
//	texture.loadFromFile("Sources/boss/boss.png");
//
//	initSprite();
//	initHitBox();
//
//	mov_speed = 100;
//	hp = 1000;
//}
//
//
//Boss::~Boss()
//{
//}
//
//void Boss::update(sf::Time deltaTime, GameCharacter* target, std::vector<sf::FloatRect> collision)
//{
//	//MOVE
//	float dX = target->getPosition().x - this->_sprite.getPosition().x;
//	float dY = target->getPosition().y - this->_sprite.getPosition().y;
//
//	float lenght = sqrt(pow(dX, 2) + pow(dY, 2));
//
//	sf::Vector2f normVect(dX / lenght, dY / lenght);
//
//	this->_sprite.move(normVect * this->mov_speed * deltaTime.asSeconds());
//	hit_box.setPosition(getPosition());
//
//	gui.updateText(hp, getPosition());
//
//	//ROTATE
//	const float PI = 3.14159265f;
//	float deg = atan2(normVect.y, normVect.x) * 180.f / PI;
//
//	this->_sprite.setRotation(deg);
//
//	//MURI
//	for (int i = 0; i != collision.size(); i++)
//	{
//		if (sat_test(hit_box.getGlobalBounds(), collision[i], &out_mtv))
//		{
//			_sprite.move(out_mtv);
//		}
//	}
//}
//
//bool Boss::isShooting(sf::Time deltaTime)
//{
//	return false;
//}
//
//void Boss::initSprite()
//{
//	_sprite.setTexture(texture);
//	_sprite.setScale(1.5, 1.5);
//	_sprite.setPosition(600.f, 600.f);
//	_sprite.setOrigin(+18, +16);
//}
//
//void Boss::initHitBox()
//{
//	hit_box.setSize(sf::Vector2f(25.f, 25.f));
//	hit_box.setOutlineColor(sf::Color::Transparent);
//	hit_box.setOutlineThickness(10.f);
//	hit_box.setFillColor(sf::Color::Transparent);
//	hit_box.setScale(_sprite.getScale());
//	hit_box.setPosition(getPosition());
//	hit_box.setOrigin(+18, +13);
//}
//
//void Boss::reload(sf::Time deltaTime)
//{
//}

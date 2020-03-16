#include "Boost.h"

Boost::Boost(sf::Vector2f spawn_pos, BoostType::Type type, const sf::Texture & texture)
{
	this->pos = spawn_pos;

	switch (type)
	{
	case 1: // 1 = HP
		this->b_type = type;
		initHp(spawn_pos, texture);
		break;

	case 2: // 2 = MS
		this->b_type = type;
		initMs(spawn_pos, texture);
		break;
	}
}

Boost::~Boost()
{
}

bool Boost::checkCollide(sf::FloatRect character)
{
	return(sat_test(character, getHitBox().getGlobalBounds(), &vec));
}

void Boost::boostSubject(std::shared_ptr<Character> character)
{
	switch (b_type)
	{
	case BoostType::HP:
		if (character->getHp() < character->getHpMax())
		{
			character->boostHeal();
			this->alive = false;
		}
		break;
	case BoostType::MS:
		if (character->getMovSpeed() == character->getMovSpeedDef())
		{
			character->boostMovSpeed();
			this->alive = false;
		}
		break;
	}
}

BoostType::Type Boost::getType()
{
	return
		this->b_type;
}

void Boost::initHp(sf::Vector2f spawn_pos, const sf::Texture & texture)
{
	initSpriteHp(spawn_pos, texture);
	initHitBoxHp();
}

void Boost::initMs(sf::Vector2f spawn_pos, const sf::Texture & texture)
{
	initSpriteMs(spawn_pos, texture);
	initHitBoxMs();
}

//void Boost::initPos()
//{
//	sf::Vector2f vec1_1(327, 327);  //TOP_LEFT
//	sf::Vector2f vec1_2(903, 327);  //TOP_RIGHT
//	sf::Vector2f vec2_1(327, 903);  //DOWN_LEFT
//	sf::Vector2f vec2_2(903, 903);  //DOWN_RIGHT
//
//	while (this->pos == sf::Vector2f(0,0))
//	{
//		switch (int i = rand() % 4)
//		{
//		case 0:
//			if (!boost_pos->pos1_1)
//			{
//				this->pos = vec1_1;
//				boost_pos->pos1_1 = true;
//				position = TOP_LEFT;
//				break;
//			}
//
//		case 1:
//			if (!boost_pos->pos1_2)
//			{
//				this->pos = vec1_2;
//				boost_pos->pos1_2 = true;
//				position = TOP_RIGHT;
//				break;
//			}
//
//		case 2:
//			if (!boost_pos->pos2_1)
//			{
//				this->pos = vec2_1;
//				boost_pos->pos2_1 = true;
//				position = DOWN_LEFT;
//				break;
//			}
//
//		case 3:
//			if (!boost_pos->pos2_2)
//			{
//				this->pos = vec2_2;
//				boost_pos->pos2_2 = true;
//				position = DOWN_RIGHT;
//				break;
//			}
//		}
//	}
//}

void Boost::initSpriteHp(sf::Vector2f spawn_pos, const sf::Texture & texture)
{ 
	sprite.setTexture(texture);	   //TEXTURE
	sprite.setScale(0.1f, 0.1f);   //SCALE
	sprite.setPosition(spawn_pos); //POS
	sprite.setOrigin(0, 0);        //ORIGIN
}

void Boost::initHitBoxHp()
{
	hit_box.setSize(sf::Vector2f(512 , 512));        //SIZE
	hit_box.setOutlineColor(sf::Color::Transparent); //COLOR
	hit_box.setOutlineThickness(3.f);
	hit_box.setFillColor(sf::Color::Transparent);
	hit_box.setScale(sprite.getScale());             //SCALE
	hit_box.setPosition(getPosition());              //POS
	hit_box.setOrigin(0, 0);                         //ORIGIN
}

void Boost::initSpriteMs(sf::Vector2f spawn_pos, const sf::Texture & texture)
{
	sprite.setTexture(texture);	   //TEXTURE
	sprite.setScale(0.05f, 0.05f); //SCALE
	sprite.setPosition(spawn_pos); //POS
	sprite.setOrigin(0, 0);        //ORIGIN
}

void Boost::initHitBoxMs()
{
	hit_box.setSize(sf::Vector2f(1200, 1200));        //SIZE
	hit_box.setOutlineColor(sf::Color::Transparent);  //COLOR
	hit_box.setOutlineThickness(3.f);
	hit_box.setFillColor(sf::Color::Transparent);
	hit_box.setScale(sprite.getScale());             //SCALE
	hit_box.setPosition(getPosition());              //POS
	hit_box.setOrigin(0, 0);                         //ORIGIN
}

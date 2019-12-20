#include "Boost.h"

Boost::Boost(const std::shared_ptr<BoostPos> boost_pos, const std::shared_ptr<EntityData> entitydata)
{
	this->entitydata = entitydata;

	this->boost_pos = boost_pos;
	this->alive = true;
	this->pos = sf::Vector2f(0, 0);

	switch (int i = rand() % 2)
	{
	case 0: this->type = HP;
		initHp();
		break;

	case 1: this->type = MS;
		initMs();
		break;
	}
}


Boost::~Boost()
{
}

void Boost::update()
{
	if (sat_test(entitydata->player->getHitBox().getGlobalBounds(), getHitBox().getGlobalBounds(), &vec))
	{
		switch (type)
		{
		case HP:
			if (entitydata->player->getHp() < entitydata->player->getHpMax())
			{
				entitydata->player->boostHeal();
				this->alive = false;

				switch (this->position)
				{
				case TOP_LEFT: boost_pos->pos1_1 = false;
					break;
				case TOP_RIGHT: boost_pos->pos1_2 = false;
					break;
				case DOWN_LEFT: boost_pos->pos2_1 = false;
					break;
				case DOWN_RIGHT: boost_pos->pos2_2 = false;
					break;
				}
			}
			break;
		case MS:
			if (entitydata->player->getMovSpeed() == entitydata->player->getMovSpeedDef())
			{
				entitydata->player->boostMovSpeed();
				this->alive = false;

				switch (this->position)
				{
				case TOP_LEFT: boost_pos->pos1_1 = false;
					break;
				case TOP_RIGHT: boost_pos->pos1_2 = false;
					break;
				case DOWN_LEFT: boost_pos->pos2_1 = false;
					break;
				case DOWN_RIGHT: boost_pos->pos2_2 = false;
					break;
				}
			}
			break;
		}
	}
}

void Boost::initHp()
{
	initPos();
	initSpriteHp();
	initHitBoxHp();
}

void Boost::initMs()
{
	initPos();
	initSpriteMs();
	initHitBoxMs();
}

void Boost::initPos()
{
	sf::Vector2f vec1_1(327, 327);  //TOP_LEFT
	sf::Vector2f vec1_2(903, 327);  //TOP_RIGHT
	sf::Vector2f vec2_1(327, 903);  //DOWN_LEFT
	sf::Vector2f vec2_2(903, 903);  //DOWN_RIGHT

	while (this->pos == sf::Vector2f(0,0))
	{
		switch (int i = rand() % 4)
		{
		case 0:
			if (!boost_pos->pos1_1)
			{
				this->pos = vec1_1;
				boost_pos->pos1_1 = true;
				position = TOP_LEFT;
				break;
			}

		case 1:
			if (!boost_pos->pos1_2)
			{
				this->pos = vec1_2;
				boost_pos->pos1_2 = true;
				position = TOP_RIGHT;
				break;
			}

		case 2:
			if (!boost_pos->pos2_1)
			{
				this->pos = vec2_1;
				boost_pos->pos2_1 = true;
				position = DOWN_LEFT;
				break;
			}

		case 3:
			if (!boost_pos->pos2_2)
			{
				this->pos = vec2_2;
				boost_pos->pos2_2 = true;
				position = DOWN_RIGHT;
				break;
			}
		}
	}
}

void Boost::initSpriteHp()
{
	sprite.setTexture(entitydata->textures->get(Textures::HP));    //TEXTURE
	sprite.setScale(0.1f, 0.1f);     //SCALE
	sprite.setPosition(this->pos); //POS
	sprite.setOrigin(0, 0);        //ORIGIN
}

void Boost::initHitBoxHp()
{
	hit_box.setSize(sf::Vector2f(512 , 512));        //SIZE
	hit_box.setOutlineColor(sf::Color::Transparent);         //COLOR
	hit_box.setOutlineThickness(3.f);
	hit_box.setFillColor(sf::Color::Transparent);
	hit_box.setScale(sprite.getScale());             //SCALE
	hit_box.setPosition(getPosition());              //POS
	hit_box.setOrigin(0, 0);                         //ORIGIN
}

void Boost::initSpriteMs()
{
	sprite.setTexture(entitydata->textures->get(Textures::MS));    //TEXTURE
	sprite.setScale(0.05f, 0.05f);     //SCALE
	sprite.setPosition(this->pos); //POS
	sprite.setOrigin(0, 0);        //ORIGIN
}

void Boost::initHitBoxMs()
{
	hit_box.setSize(sf::Vector2f(1200, 1200));        //SIZE
	hit_box.setOutlineColor(sf::Color::Transparent);         //COLOR
	hit_box.setOutlineThickness(3.f);
	hit_box.setFillColor(sf::Color::Transparent);
	hit_box.setScale(sprite.getScale());             //SCALE
	hit_box.setPosition(getPosition());              //POS
	hit_box.setOrigin(0, 0);                         //ORIGIN
}

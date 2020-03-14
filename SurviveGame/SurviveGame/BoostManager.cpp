#include "BoostManager.h"



BoostManager::BoostManager(const sf::Texture *txt_hp, const sf::Texture &txt_ms)
{
	texture = txt_hp;
	textures.load(txt_hp);
	textures.emplace_back(txt_ms);

	pos1_1 = false; 
	pos1_2 = false; 
	pos2_1 = false; 
	pos2_2 = false;
}


BoostManager::~BoostManager()
{

}

void BoostManager::spawn()
{
	if (boosts.size() < 4)
	{
		if (boost_time.getElapsedTime() > rand_time)
		{
			Boost boost(calculateSpawnPos(), textures);

			this->boosts.emplace_back(boost);
			this->boost_time.restart();
			this->rand_time = sf::seconds((rand() % 10) + 5.f);
		}
	}
}

sf::Vector2f BoostManager::calculateSpawnPos()
{
	sf::Vector2f vec1_1(327, 327);  //TOP_LEFT
	sf::Vector2f vec1_2(903, 327);  //TOP_RIGHT
	sf::Vector2f vec2_1(327, 903);  //DOWN_LEFT
	sf::Vector2f vec2_2(903, 903);  //DOWN_RIGHT

	while (this->pos == sf::Vector2f(0, 0))
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

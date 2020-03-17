#pragma once
#include <SFML/Graphics.hpp>
#include "boost.h"
#include "TextureHolder.h"

class BoostManager
{
public:
	BoostManager();
	~BoostManager();


	void setTextures(sf::Texture txt_hp, sf::Texture txt_ms);
	void spawn();
	void resetBoostTime();
	bool canSpawn();

	int checkCollisionType(sf::FloatRect character);
	void renderBoosts(std::shared_ptr<sf::RenderWindow> target);
private:
	sf::Vector2f calculateSpawnPos();

	sf::Clock boost_time;
	sf::Time rand_time;

	std::vector<Boost> boosts;
	std::map<BoostType::Type, sf::Texture> textures;
	bool pos1_1;
	bool pos1_2;
	bool pos2_1;
	bool pos2_2;

	sf::Vector2f vec1_1;  //TOP_LEFT
	sf::Vector2f vec1_2;  //TOP_RIGHT
	sf::Vector2f vec2_1;  //DOWN_LEFT
	sf::Vector2f vec2_2;  //DOWN_RIGHT
};


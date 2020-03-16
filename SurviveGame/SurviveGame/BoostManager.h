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

	int checkIfType(sf::FloatRect character);
	void renderBoosts(std::shared_ptr<sf::RenderWindow> target);
private:
	sf::Vector2f calculateSpawnPos();

	sf::Clock boost_time;
	sf::Time rand_time;

	std::vector<Boost> boosts;
	/*TextureHolder textures;*/
	std::map<BoostType::Type, std::unique_ptr<sf::Texture>> textures;
	sf::Vector2f pos;
	/*std::map<Pos, std::shared_ptr<Boost>> boosts;*/
	bool pos1_1;
	bool pos1_2;
	bool pos2_1;
	bool pos2_2;

	sf::Vector2f vec1_1;  //TOP_LEFT
	sf::Vector2f vec1_2;  //TOP_RIGHT
	sf::Vector2f vec2_1;  //DOWN_LEFT
	sf::Vector2f vec2_2;  //DOWN_RIGHT
};


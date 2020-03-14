#pragma once

#include <SFML/Graphics.hpp>
#include "boost.h"
#include "TextureHolder.h"

class BoostManager
{
public:
	BoostManager(const sf::Texture &txt_hp, const sf::Texture &txt_ms);
	~BoostManager();

	void spawn();

private:
	bool pos1_1;
	bool pos1_2;
	bool pos2_1;
	bool pos2_2;

	sf::Vector2f calculateSpawnPos();

	sf::Clock boost_time;
	sf::Time rand_time;

	std::vector<Boost> boosts;

	TextureHolder textures;
	std::unique_ptr<sf::Texture> texture;
};


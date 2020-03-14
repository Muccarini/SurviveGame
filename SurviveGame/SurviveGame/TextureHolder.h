#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

namespace Textures
{
	enum ID { Personaggio, PersonaggioMS, ShotgunP, RifleP, HandgunP, Enemy, Proiettile, Boss, Pet, HP, MS};
}



class TextureHolder   //NO COSTRU PERCHE MAP VUOTA
{
public:
	
	void load(Textures::ID id, const std::string& filename);
	void load(Textures::ID id, std::unique_ptr<sf::Texture> texture);

	const sf::Texture& get(Textures::ID id) const;

private:
	std::map<Textures::ID, std::unique_ptr<sf::Texture>> texture_map;
};


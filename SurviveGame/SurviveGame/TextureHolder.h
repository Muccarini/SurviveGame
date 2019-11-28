#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

namespace Textures
{
	enum ID { Personaggio, Enemy, Proiettile, Boss};
}



class TextureHolder   //NO COSTRU PERCHE MAP VUOTA, NO DESTR PER UNIQUE_PTR
{
public:
	
	void load(Textures::ID id, const std::string& filename);
	const sf::Texture& get(Textures::ID id) const;

private:
	std::map<Textures::ID, std::unique_ptr<sf::Texture>> _textureMap;
};


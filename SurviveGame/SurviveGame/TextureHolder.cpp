#include "TextureHolder.h"
#include <assert.h>

void TextureHolder::load(Textures::ID id, const std::string & filename)
{
	std::unique_ptr<sf::Texture> texture(new sf::Texture());
	if (!texture->loadFromFile(filename))
	{//THROW ERROR
		throw std::runtime_error("il file" + filename + "errore");

		auto inserted = _textureMap.insert(std::make_pair(id, std::move(texture)));
		//assert(inserted.second);
		
	}

	texture->loadFromFile(filename);

	_textureMap.insert(std::make_pair(id, std::move(texture)));
}

const sf::Texture & TextureHolder::get(Textures::ID id) const
{
	auto found = _textureMap.find(id);
	//assert(found != _textureMap.find(id));

	return *found->second;
}

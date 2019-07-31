#include "Enemy.h"



Enemy::Enemy()
{
	_textures.load(Textures::Personaggio, "Sources/Sprite_laila_run2.png");
	_sprite.setTexture(_textures.get(Textures::Personaggio));
	_sprite.setPosition(200.f, 200.f);
	_sprite.setTextureRect(sf::IntRect(0, 0, 32, 48));
}


Enemy::~Enemy()
{
}

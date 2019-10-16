#pragma once
#include"SFML/Graphics.hpp"
#include"TextureHolder.h"

class GameCharacter
{
public:
	GameCharacter();
	virtual ~GameCharacter();

	void render(sf::RenderWindow* target);

	//virtual void move(sf::Time deltaTime) = 0;
	//virtual void rotate(sf::Vector2f vec_dir) = 0;
	//virtual void update(sf::Time deltaTime, sf::Vector2f mousePosView);
	//virtual void update(sf::Time deltaTime, GameCharacter* target);

	sf::Vector2f getPosition();

	sf::RectangleShape hit_box;

protected:

	TextureHolder _textures;
	sf::Sprite _sprite;
	sf::Vector2f out_mtv;

	float mov_speed;


};


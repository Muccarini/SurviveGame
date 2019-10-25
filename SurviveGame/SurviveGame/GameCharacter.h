#pragma once
#include"SFML/Graphics.hpp"
#include"TextureHolder.h"

class GameCharacter
{
public:
	GameCharacter();
	virtual ~GameCharacter();

	void render(sf::RenderWindow* target);

	sf::Vector2f getPosition();

	sf::RectangleShape hit_box;

protected:

	bool sat_test(const sf::FloatRect &rectSp1, const sf::FloatRect &rectSp2, sf::Vector2f *out_mtv);

	sf::Sprite _sprite;
	sf::Vector2f out_mtv;

	float mov_speed;


};


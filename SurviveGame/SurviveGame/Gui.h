#pragma once
#include <SFML/Graphics.hpp>

class Gui
{
public:
	Gui();
	~Gui();

	void setText(int integer, sf::Vector2f view);
	//OVERLOAD WITH STRINGS void setText(sf::String string, sf::View view);

	void renderText(sf::RenderWindow * target);

	sf::Text text;
	sf::Vector2f offset_view;
};


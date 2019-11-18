#include "Gui.h"
#include <iostream>



Gui::Gui()
{
	offset_view.x = 100;
	offset_view.y = 100;
}


Gui::~Gui()
{
}

void Gui::renderText(sf::RenderWindow * target)
{
	target->draw(text);
}

void Gui::setText(int ammo, sf::Vector2f view)
{

	text.setString(std::to_string(ammo));
	text.setFillColor(sf::Color::Magenta);
	text.setCharacterSize(24);
	text.setPosition(view.x, view.y);
}

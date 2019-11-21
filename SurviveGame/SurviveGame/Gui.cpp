#include "Gui.h"
#include <iostream>



Gui::Gui()
{
	texts.push_back(ammo);
	texts.push_back(hp);
	fontInit();

	texts[0].setPosition(0, 0);
}


Gui::~Gui()
{
}

void Gui::renderTexts(sf::RenderWindow * target)
{
	for (auto i = texts.begin(); i != texts.end(); i++)
	{
		target->draw(*(i));
	}
}

void Gui::updateText(int ammo, int hp, sf::Vector2f obj)
{
	//AMMO GUI
	texts[0].setString(std::to_string(ammo));
	texts[0].setFillColor(sf::Color::Magenta);
	texts[0].setCharacterSize(15);
	texts[0].setPosition(obj.x -50, obj.y +25);

	//HP GUI
	texts[1].setString(std::to_string(hp));
	texts[1].setFillColor(sf::Color::Red);
	texts[1].setCharacterSize(15);
	texts[1].setPosition(obj.x +20, obj.y +25);
} 

void Gui::fontInit()
{
	font.loadFromFile("Sources/04B_30__.ttf");
	for (auto i = texts.begin(); i != texts.end(); i++)
	{
		(i)->setFont(font);
	}
}

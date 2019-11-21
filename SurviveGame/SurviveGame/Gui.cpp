#include "Gui.h"
#include <iostream>



Gui::Gui()
{
	texts.push_back(ammo);
	texts.push_back(hp);
	texts.push_back(dash_cd);
	fontInit();

	texts[0].setPosition(0, 0);
}


Gui::~Gui()
{
}

void Gui::renderTexts(sf::RenderWindow * target)
{
	 target->draw(texts[0]);
	 target->draw(texts[1]);
	 if (d_cd != 10)
		 target->draw(texts[2]);

}

void Gui::updateText(int hp, sf::Vector2f obj)
{
	//HP GUI
	texts[1].setString(std::to_string(hp));
	texts[1].setFillColor(sf::Color::Red);
	texts[1].setCharacterSize(15);
	texts[1].setPosition(obj.x - 8, obj.y + 30);
}

void Gui::updateText(int ammo, int hp, float dash_cd, sf::Vector2f obj)
{
	//AMMO GUI
	texts[0].setString(std::to_string(ammo));
	texts[0].setFillColor(sf::Color::Magenta);
	texts[0].setCharacterSize(15);
	texts[0].setPosition(obj.x - 50, obj.y + 25);


	//HP GUI
	texts[1].setString(std::to_string(hp));
	texts[1].setFillColor(sf::Color::Red);
	texts[1].setCharacterSize(15);
	texts[1].setPosition(obj.x + 20, obj.y + 25);

	//DASH_CD
	texts[2].setString(std::to_string(static_cast<int>(dash_cd)));
	texts[2].setFillColor(sf::Color::Blue);
	texts[2].setCharacterSize(15);
	texts[2].setPosition(obj.x + 50, obj.y -50);

	this->d_cd = static_cast<int>(dash_cd);
}

void Gui::fontInit()
{
	font.loadFromFile("Sources/04B_30__.ttf");
	for (auto i = texts.begin(); i != texts.end(); i++)
	{
		(i)->setFont(font);
	}
}

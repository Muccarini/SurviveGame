#include "Hud.h"
#include <iostream>



Hud::Hud()
{
	fontInit();

}


Hud::~Hud()
{
}

void Hud::renderTexts(sf::RenderWindow * target)
{
	 target->draw(this->ammo);
	 target->draw(this->hp);
	 if (d_cd != 10)
		 target->draw(this->dash_cd);

}

void Hud::updateText(int hp, sf::Vector2f obj)
{
	//HP GUI
	this->hp.setString(std::to_string(hp));
	this->hp.setFillColor(sf::Color::Red);
	this->hp.setCharacterSize(15);
	this->hp.setPosition(obj.x - 8, obj.y + 30);
}

void Hud::updateText(int ammo, int hp, float dash_cd, sf::Vector2f obj)
{
	//AMMO GUI
	this->ammo.setString(std::to_string(ammo));
	this->ammo.setFillColor(sf::Color::Magenta);
	this->ammo.setCharacterSize(15);
	this->ammo.setPosition(obj.x - 50, obj.y + 25);

	//HP GUI
	this->hp.setString(std::to_string(hp));
	this->hp.setFillColor(sf::Color::Red);
	this->hp.setCharacterSize(15);
	this->hp.setPosition(obj.x + 20, obj.y + 25);

	//DASH_CD
	this->dash_cd.setString(std::to_string(static_cast<int>(dash_cd)));
	this->dash_cd.setFillColor(sf::Color::Blue);
	this->dash_cd.setCharacterSize(15);
	this->dash_cd.setPosition(obj.x + 50, obj.y -50);

	this->d_cd = static_cast<int>(dash_cd);
}

void Hud::fontInit()
{
	font.loadFromFile("Sources/04B_30__.ttf");
		ammo.setFont(font);
		hp.setFont(font);
		dash_cd.setFont(font);
}

#include "Hud.h"
#include <iostream>



Hud::Hud()
{
	fontInit();
}


Hud::~Hud()
{
}

void Hud::renderTextsGui(sf::RenderWindow * target)
{
	 target->draw(this->ammo);
	 target->draw(this->hp);
	 if (d_cd != 10)
		 target->draw(this->dash_cd);

}

void Hud::renderTextsHud(sf::RenderWindow * target)
{
	if(this->kc > 0)
		target->draw(this->kill_counter);
	if(this->cd > 0.2)
		target->draw(this->countdown);
}


void Hud::updateText(int kill_counter, float countdown, sf::View view)
{
	//KILLCOUNTER
	this->kill_counter.setString(std::to_string(kill_counter));
	this->kill_counter.setFillColor(sf::Color::Red);
	this->kill_counter.setCharacterSize(30);
	this->kill_counter.setPosition(view.getCenter().x - 600, view.getCenter().y - 330);

	this->kc = kill_counter;

	//COUNTDOWN
	this->countdown.setString(std::to_string(static_cast<int>(countdown)));
	this->countdown.setFillColor(sf::Color::Red);
	this->countdown.setCharacterSize(50);
	this->countdown.setPosition(view.getCenter().x - 20, view.getCenter().y -30);

	this->cd = static_cast<int>(countdown);
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

		kill_counter.setFont(font);
		countdown.setFont(font);
}

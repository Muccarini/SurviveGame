#include "Hud.h"
#include <iostream>

Hud::Hud()
{
	fontInit();
}


Hud::~Hud()
{
}

void Hud::updateText(const int hp, const sf::Vector2f obj)
{
	//HP GUI
	this->hp.setString(std::to_string(hp));
	this->hp.setFillColor(sf::Color::Red);
	this->hp.setCharacterSize(15);
	this->hp.setPosition(obj.x - 8, obj.y + 30);
}

void Hud::updateText(const int ammo, const int hp, const sf::Vector2f obj)
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
}

void Hud::updateText(const int kills, const float countdown, const int round, const sf::View& view)
{
	//KILLCOUNTER
	this->kills.setString(std::to_string(kills));
	this->kills.setFillColor(sf::Color::Red);
	this->kills.setCharacterSize(70);
	this->kills.setPosition(view.getCenter().x - 540, view.getCenter().y - 330);

	this->kc = kills;

	//COUNTDOWN
	this->countdown.setString(std::to_string(static_cast<int>(countdown)));
	this->countdown.setFillColor(sf::Color::Red);
	this->countdown.setCharacterSize(50);
	this->countdown.setPosition(view.getCenter().x - 20, view.getCenter().y - 30);

	this->cd = static_cast<int>(countdown);

	//ROUND
	this->round.setString(std::to_string(round));
	this->round.setFillColor(sf::Color::Blue);
	this->round.setCharacterSize(70);
	this->round.setPosition(view.getCenter().x + 500, view.getCenter().y - 330);
}

void Hud::renderTextsCharacter(std::shared_ptr<sf::RenderWindow> target)
{
	 target->draw(this->ammo);
	 target->draw(this->hp);
}

void Hud::renderTextsHud(std::shared_ptr<sf::RenderWindow> target)
{
	target->draw(round);
	if(this->kc > 0)
		target->draw(this->kills);
	if(this->cd > 0.2)
		target->draw(this->countdown);
}

void Hud::fontInit()
{
	font.loadFromFile("Sources/04B_30__.ttf");

		ammo.setFont(font);
		hp.setFont(font);

		kills.setFont(font);
		countdown.setFont(font);
		round.setFont(font);
}

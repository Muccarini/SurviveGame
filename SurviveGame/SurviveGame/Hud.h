#pragma once
#include <SFML/Graphics.hpp>

class Hud
{
public:
	Hud();
	~Hud();

	void updateText(const int hp, const sf::Vector2f obj);													 //ENEMY
	void updateText(const int ammo, const int hp, const sf::Vector2f obj);									 //PLAYER
	void updateText (const int kill_counter, const float countdown, const int round, const sf::View& view);  //GAME

	void renderTextsCharacter(std::shared_ptr<sf::RenderWindow> target); //CHARACTER
	void renderTextsHud(std::shared_ptr<sf::RenderWindow> target);       //GAME

private:
	void fontInit();

	sf::Text ammo;
	sf::Text hp;
	sf::Text round;
	sf::Text kills;
	sf::Text countdown;

	int kc;
	int cd;

	sf::Font font;

};


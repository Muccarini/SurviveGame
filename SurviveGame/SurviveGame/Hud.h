#pragma once
#include <SFML/Graphics.hpp>

class Hud
{
public:
	Hud();
	~Hud();

	void updateText(int hp, sf::Vector2f obj);													 //ENEMY
	void updateText(int ammo, int hp, sf::Vector2f obj);									 //PLAYER
	void updateText (int kill_counter, float countdown, int round, const sf::View& view);  //GAME

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


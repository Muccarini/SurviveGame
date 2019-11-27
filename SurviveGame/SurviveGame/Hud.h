#pragma once
#include <SFML/Graphics.hpp>

class Hud
{
public:
	Hud();
	~Hud();

	void updateText(int hp, sf::Vector2f obj);                          //ENEMY
	void updateText(int ammo, int hp, float dash_cd, sf::Vector2f obj); //PLAYER
	void updateText(int kill_counter, float countdown, sf::View view);  //VIEW

	void renderTextsGui(sf::RenderWindow * target);
	void renderTextsHud(sf::RenderWindow * target);

private:
	void fontInit();

	sf::Text ammo;
	sf::Text hp;
	sf::Text dash_cd;
	int d_cd;

	sf::Text kill_counter;
	int kc;
	sf::Text countdown;
	int cd;

	sf::Font font;
	sf::Vector2f offset_view;

};


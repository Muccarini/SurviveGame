#pragma once
#include <SFML/Graphics.hpp>

class Hud
{
public:
	Hud();
	~Hud();

	void updateText(int hp, sf::Vector2f obj);
	void updateText(int ammo, int hp, float dash_cd, sf::Vector2f obj);

	void renderTexts(sf::RenderWindow * target);

private:
	void fontInit();

	sf::Text ammo;
	sf::Text hp;
	sf::Text dash_cd;
	int d_cd;

	sf::Font font;
	sf::Vector2f offset_view;
};


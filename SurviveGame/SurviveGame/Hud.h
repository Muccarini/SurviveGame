#pragma once
#include <SFML/Graphics.hpp>

class Hud
{
public:
	Hud();
	~Hud();

	void updateText(const int hp, const  sf::Vector2f obj);                                                //ENEMY
	void updateText(const int ammo, const int hp, const float dash_cd, const sf::Vector2f obj);            //PLAYER
	void updateText(const int kill_counter, const float countdown, const int round, const sf::View view);  //VIEW

	void renderTextsGui(std::shared_ptr<sf::RenderWindow> target);
	void renderTextsHud(std::shared_ptr<sf::RenderWindow> target);

private:
	void fontInit();

	sf::Text ammo;
	sf::Text hp;
	sf::Text dash_cd;
	int d_cd;

	sf::Text kills;
	int kc;
	sf::Text countdown;
	int cd;

	sf::Text round;

	sf::Font font;
	sf::Vector2f offset_view;

};


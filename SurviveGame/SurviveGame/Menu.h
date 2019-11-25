#pragma once
#include <SFML/Graphics.hpp>

class Menu
{
public:
	Menu();
	~Menu();
	void initMainMenu();

	private:
	sf::RectangleShape background;
};


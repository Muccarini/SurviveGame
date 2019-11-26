#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "GameLogic.h"

class MainMenu : 
	public State
{
public:
	MainMenu();
	~MainMenu();

	void initMainMenu();
	void update(sf::Time deltaTime);
	void render();

	private:
	sf::Texture background_txt;
	sf::Sprite background;
};


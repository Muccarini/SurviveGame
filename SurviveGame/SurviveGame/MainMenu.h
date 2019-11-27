#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "GameLogic.h"
#include "Button.h"

class MainMenu : 
	public State
{
public:
	MainMenu();
	~MainMenu();

	void update(sf::Time deltaTime);
	void render();

private:
	void initMainMenu();
	void initButtons();
	void initBackground();

	void updateButtons();

	sf::Texture background_txt;
	sf::Sprite background;

	Button new_game;
	Button settings;
	Button exit;
};


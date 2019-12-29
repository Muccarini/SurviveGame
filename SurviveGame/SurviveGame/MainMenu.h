#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "GameLogic.h"
#include "SelectionCharacter.h"
#include "Button.h"

class MainMenu : 
	public State
{
public:
	MainMenu();
	virtual ~MainMenu();

	void update(sf::Time deltaTime);
	void render();

private:
	void initButtons();
	void initBackground();

	void updateButtons();

	sf::Texture background_txt;
	sf::Sprite background;

	Button new_game;
	Button settings;
	Button exit;
};


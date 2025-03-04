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

private:
	virtual void update(const sf::Time& delta_time);
	virtual void render();

	void initButtons();
	void initBackground();

	void updateButtons();

	sf::Texture background_txt;
	sf::Sprite background;

	Button new_game;
	Button exit;
};


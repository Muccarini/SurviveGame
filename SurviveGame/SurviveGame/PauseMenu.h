#pragma once
#include "State.h"
#include "Button.h"

class PauseMenu :
	public State
{
public:
	PauseMenu();
	virtual ~PauseMenu();

	void update(sf::Time deltaTime);
	void render();

private:
	void initButtons();
	void initBackground();

	void updateButtons();

	sf::Texture background_txt;
	sf::Sprite background;

	Button resume;
	Button exit_game;


};


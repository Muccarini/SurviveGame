#pragma once
#include "State.h"
#include "Button.h"

class PauseMenu :
	public State
{
public:
	PauseMenu();
	virtual ~PauseMenu();

private:

	virtual void update(sf::Time deltaTime);
	virtual void render();

	void initButtons();
	void initBackground();

	void updateButtons();

	sf::Texture background_txt;
	sf::Sprite background;

	Button resume;
	Button exit_game;


};


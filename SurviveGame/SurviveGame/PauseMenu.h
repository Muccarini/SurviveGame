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

	virtual void update(const sf::Time& delta_time);
	virtual void render();

	void initButtons();
	void initBackground();

	void updateButtons();

	sf::Texture background_txt;
	sf::Sprite background;

	Button resume;
	Button exit_game;


};


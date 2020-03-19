#pragma once
#include "State.h"
#include "Button.h"
#include "GameLogic.h"

class SelectionCharacter :
	public State
{
public:
	SelectionCharacter();
	virtual ~SelectionCharacter() = default;

private:

	virtual void update(const sf::Time& deltaTime);
	virtual void render();

	void initButtons();
	void initBackground();

	void updateButtons();

	sf::Sprite background;
	sf::Texture background_txt;

	sf::Texture shotguntxt;
	sf::Texture rifletxt;
	sf::Texture guntxt;


	Button shotgun;
	Button rifle;
	Button gun;
};
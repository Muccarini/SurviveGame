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

	void update(sf::Time deltaTime);
	void render();

private:
	void initButtons();
	void initBackground();

	void updateButtons();

	sf::Sprite background;
	sf::Texture background_txt;

	sf::Texture shotguntxt;
	sf::Texture rifletxt;
	sf::Texture knifetxt;


	Button shotgun;
	Button rifle;
	Button knife;
};
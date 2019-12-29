#include "SelectionCharacter.h"
#include "StShotgunPlayerFight.h"
#include "StRiflePlayerFight.h"

SelectionCharacter::SelectionCharacter()
{
	initBackground();
	initButtons();
}

void SelectionCharacter::update(sf::Time deltaTime)
{
	window->setView(window->getDefaultView());
	updateMousePos();
	updateButtons();
	render();
}

void SelectionCharacter::render()
{
	window->draw(background);
	shotgun.draw(window);
	rifle.draw(window);
	knife.draw(window);
}

void SelectionCharacter::initButtons()
{
	this->shotguntxt.loadFromFile("Sources/Top_Down_Survivor/shotgun/move/survivor-move_shotgun_0.png");
	shotgun.setBox(sf::Vector2f(313.f, 206.f), sf::Color::White, 2, sf::Color::Transparent, sf::Vector2f(300, 320), &shotguntxt);

	this->rifletxt.loadFromFile("Sources/Top_Down_Survivor/rifle/move/survivor-move_rifle_0.png");
	rifle.setBox(sf::Vector2f(313.f, 206.f), sf::Color::White, 2, sf::Color::Transparent, sf::Vector2f(759, 320.f), &rifletxt);

	this->knifetxt.loadFromFile("Sources/Top_Down_Survivor/knife/move/survivor-move_knife_0.png");
	knife.setBox(sf::Vector2f(313.f, 206.f), sf::Color::White, 2, sf::Color::Transparent, sf::Vector2f(1200, 320), &knifetxt);
}

void SelectionCharacter::initBackground()
{
	background_txt.loadFromFile("Sources/background.jpg");
	background.setTexture(background_txt);
}

void SelectionCharacter::updateButtons()
{
	//SHOTGUN
	if (shotgun.isActive(mouse_pos_view))
	{
		StrategyFight* stf = new StShotgunPlayerFight();
		this->states->push(new GameLogic(Textures::ID::ShotgunP, stf));
		this->states->top()->window = this->window;
		this->states->top()->states = this->states;
		return;
	}

	//RIFLE
	if (rifle.isActive(mouse_pos_view))
	{
		StrategyFight* stf = new StRiflePlayerFight();
		this->states->push(new GameLogic(Textures::ID::RifleP, stf));
		this->states->top()->window = this->window;
		this->states->top()->states = this->states;
		return;
	}

	//KNIFE
	if (knife.isActive(mouse_pos_view))
	{
		StrategyFight* stf = new StShotgunPlayerFight();
		this->states->push(new GameLogic(Textures::ID::KnifeP, stf));
		this->states->top()->window = this->window;
		this->states->top()->states = this->states;
		return;
	}


}

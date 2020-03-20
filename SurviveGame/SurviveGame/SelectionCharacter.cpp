#include "SelectionCharacter.h"
#include "StShotgunPlayerFight.h"
#include "StRiflePlayerFight.h"
#include "StGunPlayerFight.h"

SelectionCharacter::SelectionCharacter()
{
	initBackground();
	initButtons();
}

void SelectionCharacter::update(const sf::Time& delta_time)
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
	gun.draw(window);
}

void SelectionCharacter::initButtons()
{
	this->shotguntxt.loadFromFile("Sources/Top_Down_Survivor/shotgun/move/survivor-move_shotgun_0.png");
	shotgun.setBox(sf::Vector2f(313.f, 206.f), sf::Color::White, 4, sf::Color::Transparent, sf::Vector2f(300, 320), &shotguntxt);

	this->rifletxt.loadFromFile("Sources/Top_Down_Survivor/rifle/move/survivor-move_rifle_0.png");
	rifle.setBox(sf::Vector2f(313.f, 206.f), sf::Color::White, 4, sf::Color::Transparent, sf::Vector2f(759, 320.f), &rifletxt);

	this->guntxt.loadFromFile("Sources/Top_Down_Survivor/handgun/move/survivor-move_handgun_0.png");
	gun.setBox(sf::Vector2f(313.f, 206.f), sf::Color::White, 4, sf::Color::Transparent, sf::Vector2f(1200, 320), &guntxt);
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
		this->states->push(new GameLogic(Textures::ID::ShotgunP, std::make_shared<StShotgunPlayerFight>(StShotgunPlayerFight())));
		this->states->top()->window = this->window;
		this->states->top()->states = this->states;
		return;
	}

	//RIFLE
	else if (rifle.isActive(mouse_pos_view))
	{
		this->states->push(new GameLogic(Textures::ID::RifleP, std::make_shared<StRiflePlayerFight>(StRiflePlayerFight())));
		this->states->top()->window = this->window;
		this->states->top()->states = this->states;
		return;
	}

	//HANDGUN
	else if (gun.isActive(mouse_pos_view))
	{
		this->states->push(new GameLogic(Textures::ID::HandgunP, std::make_shared<StGunPlayerFight>(StGunPlayerFight())));
		this->states->top()->window = this->window;
		this->states->top()->states = this->states;
		return;
	}
}

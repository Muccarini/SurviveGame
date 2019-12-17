#include "PauseMenu.h"



PauseMenu::PauseMenu()
{
	initBackground();
	initButtons();
}


PauseMenu::~PauseMenu()
{
}

void PauseMenu::update(sf::Time deltaTime)
{
	window->setView(window->getDefaultView());
	updateMousePos();
	updateButtons();
	render();
}

void PauseMenu::render()
{
	window->draw(background);
	resume.draw(window);
	exit_game.draw(window);
}

void PauseMenu::initBackground()
{
	background_txt.loadFromFile("Sources/background.jpg");
	background.setTexture(background_txt);
}

void PauseMenu::updateButtons()
{
	//RESUME
	        //hover
	if (resume.isHover(mouse_pos_view))
	{
		resume.buttonAnimation();
	}
	else
		resume.setStandard();

	        //click
	if (resume.isActive(mouse_pos_view))
	{
		this->states->top()->endState();
	}

	//EXIT GAME
	        //hover
	if (exit_game.isHover(mouse_pos_view))
	{
		exit_game.buttonAnimation();
	}
	else
		exit_game.setStandard();

	        //click
	if (exit_game.isActive(mouse_pos_view))
	{
		this->window->close();
	}
}

void PauseMenu::initButtons()
{
	resume.setText("Sources/edunline.ttf", "RESUME", sf::Color::Black, 100.f, sf::Vector2f(660.f, 200.f));
	resume.setBox(sf::Vector2f(355, 70.f), sf::Color::Magenta, 3.f, sf::Color::Transparent, sf::Vector2f(660.f, 230.f));

	exit_game.setText("Sources/edunline.ttf", "Exit Game", sf::Color::Black, 70.f, sf::Vector2f(900.f, 600.f));
	exit_game.setBox(sf::Vector2f(355.f, 50.f), sf::Color::Magenta, 3.f, sf::Color::Transparent, sf::Vector2f(900.f, 620.f));
}

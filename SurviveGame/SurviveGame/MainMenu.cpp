#include "MainMenu.h"



MainMenu::MainMenu()
{
	initMainMenu();
}

MainMenu::~MainMenu()
{
}

void MainMenu::initMainMenu()
{
	initButtons();
	initBackground();
}

void MainMenu::initButtons()
{
	new_game.setText("Sources/edunline.ttf", "New Game", sf::Color::Black, 100.f, sf::Vector2f(660.f, 200.f));
	new_game.setBox(sf::Vector2f(500.f, 70.f), sf::Color::Magenta, 3.f, sf::Color::Transparent, sf::Vector2f(660.f, 230.f));

	settings.setText("Sources/edunline.ttf", "Settings", sf::Color::Black, 70.f, sf::Vector2f(660.f, 300.f));
	settings.setBox(sf::Vector2f(300.f, 50.f), sf::Color::Magenta, 3.f, sf::Color::Transparent, sf::Vector2f(660.f, 320.f));

	exit.setText("Sources/edunline.ttf", "Exit", sf::Color::Black, 70.f, sf::Vector2f(900.f, 600.f));
	exit.setBox(sf::Vector2f(135.f, 50.f), sf::Color::Magenta, 3.f, sf::Color::Transparent, sf::Vector2f(900.f, 620.f));

}

void MainMenu::initBackground()
{
	background_txt.loadFromFile("Sources/background.jpg");
	background.setTexture(background_txt);
}

void MainMenu::updateButtons()
{
	if (new_game.isHover(mouse_pos_view))
	{
		new_game.buttonAnimation();
	}
	else
		new_game.setStandard();

	if (new_game.isActive(mouse_pos_view))
	{
		this->states->push(new GameLogic());
		this->states->top()->window = this->window;
		this->states->top()->states = this->states;
	}
}

void MainMenu::update(sf::Time deltaTime)
{
	updateMousePos();
	updateButtons();
	render();
}

void MainMenu::render()
{
	window->draw(background);
	new_game.draw(window);
	settings.draw(window);
	exit.draw(window);
}

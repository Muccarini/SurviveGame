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
	background_txt.loadFromFile("Sources/background.jpg");
	background.setTexture(background_txt);
}

void MainMenu::update(sf::Time deltaTime)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		this->states->push(new GameLogic());
		this->states->top()->window = this->window;
		this->states->top()->states = this->states;
	}
	render();
}

void MainMenu::render()
{
	window->draw(background);
}
